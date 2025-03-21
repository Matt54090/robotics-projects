/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define GPIO_BASE_PATH "/sys/devices/platform/soc"
#define GPIO_CLASS_PATH "/sys/class/gpio"

enum {
    OFF,
    ON
};

enum gpio_info_e {
    GPIO_BASE_ADDR = 0xfe200000,
    IO_PORT = 18,

    TOTAL_GPIO = 58
};

struct gpio_ctrl {
    int direction;
    int value;
};

struct gpio_sysfs {
    int base;
    int export;
    struct gpio_ctrl *ctrl;
};

static struct gpio_sysfs *_init_gpio(void);
static int _exit_gpio(struct gpio_sysfs *del);

static int _find_gpio_base(void);

static int _init_gpio_export(void);
static int _exit_gpio_export(int fd);

static int _init_gpio_direction(int num);
static int _exit_gpio_direction(int fd);

static int _init_gpio_value(int num);
static int _exit_gpio_value(int fd);

static int _set_gpio_output(struct gpio_sysfs *sysfs, int pin);
static int _write_gpio(struct gpio_sysfs *sysfs, int pin, int value);

static void _handler_for_ctrl_c(int signo);

static inline int _get_base_num(const char *str);

static inline int _open_gpio(const char *path);
static inline int _close_gpio(int fd);

static inline int _check_permission(void);

static int g_escape = OFF;

int main(void)
{
    if (_check_permission() != 0)
    {
        fprintf(stderr, "[JCRT ERR] Need to execute as root!\n");
        return -EPERM;
    }

    struct sigaction sig_act = {
        .sa_handler = _handler_for_ctrl_c,
        .sa_flags = 0,
    };
    sigemptyset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);

    struct gpio_sysfs *gpio = _init_gpio();
    if (gpio == NULL)
        return -EPERM;

    int ret = _set_gpio_output(gpio, IO_PORT);
    if (ret == 0)
    {
        while (g_escape == OFF)
        {
            _write_gpio(gpio, IO_PORT, ON);
            printf("[JCRT] GPIO set!\n");
            sleep(1);

            _write_gpio(gpio, IO_PORT, OFF);
            printf("[JCRT] GPIO clear.\n");
            sleep(1);
        }
    }

    _exit_gpio(gpio);

    return 0;
}

static struct gpio_sysfs *_init_gpio(void)
{
    struct gpio_sysfs *new = malloc(sizeof(struct gpio_sysfs));
    if (new == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Memory allocation failed.\n");
        return NULL;
    }

    memset(new, 0x0, sizeof(struct gpio_sysfs));

    new->base = _find_gpio_base();
    if (new->base < 0)
    {
        _exit_gpio(new);
        return NULL;
    }

    new->export = _init_gpio_export();
    if (new->export < 0)
    {
        _exit_gpio(new);
        return NULL;
    }

    new->ctrl = malloc(sizeof(struct gpio_ctrl) * TOTAL_GPIO);
    if (new->ctrl == NULL)
    {
        _exit_gpio(new);
        return NULL;
    }
    memset(new->ctrl, 0x0, sizeof(struct gpio_ctrl) * TOTAL_GPIO);

    return new;
}

static int _exit_gpio(struct gpio_sysfs *del)
{
    if (del == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    if (del->ctrl)
    {
        struct gpio_ctrl *ctrl;
        for (int i = 0; i < TOTAL_GPIO; i++)
        {
            ctrl = &del->ctrl[i];

            if (ctrl->direction > 0)
                _exit_gpio_direction(ctrl->direction);

            if (ctrl->value > 0)
                _exit_gpio_value(ctrl->value);
        }

        free(del->ctrl);
    }

    _exit_gpio_export(del->export);

    free(del);
    del = NULL;

    return 0;
}

static int _find_gpio_base(void)
{
    char path[128] = {
        0,
    };

    snprintf(path, sizeof(path), "%s/%x.gpio/gpio", GPIO_BASE_PATH,
             GPIO_BASE_ADDR);

    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Failed to open directory: %s\n", path);
        return -EPERM;
    }

    int base = -EPERM;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, "gpiochip"))
        {
            base = _get_base_num(entry->d_name);
            break;
        }
    }

    closedir(dir);

    return base;
}

static int _init_gpio_export(void)
{
    char path[128] = {
        0,
    };

    snprintf(path, sizeof(path), "%s/export", GPIO_CLASS_PATH);
    return _open_gpio(path);
}

static int _exit_gpio_export(int fd)
{
    char path[128] = {
        0,
    };
    snprintf(path, sizeof(path), "%s/unexport", GPIO_CLASS_PATH);

    int unexport = _open_gpio(path);
    if (unexport > 0)
    {
        char gpio[8] = {
            0,
        };
        DIR *dir = opendir(GPIO_CLASS_PATH);

        int num;
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strstr(entry->d_name, "gpiochip"))
                continue;

            if (strstr(entry->d_name, "gpio"))
            {
                sscanf(entry->d_name, "gpio%d", &num);
                snprintf(gpio, sizeof(gpio), "%d", num);
                write(unexport, gpio, strlen(gpio));
            }
        }

        closedir(dir);
        _close_gpio(unexport);
    }

    return _close_gpio(fd);
}

static int _init_gpio_direction(int num)
{
    char path[128] = {
        0,
    };

    snprintf(path, sizeof(path), "%s/gpio%d/direction", GPIO_CLASS_PATH, num);
    return _open_gpio(path);
}

static int _exit_gpio_direction(int fd)
{
    return _close_gpio(fd);
}

static int _init_gpio_value(int num)
{
    char path[128] = {
        0,
    };

    snprintf(path, sizeof(path), "%s/gpio%d/value", GPIO_CLASS_PATH, num);
    return _open_gpio(path);
}

static int _exit_gpio_value(int fd)
{
    return _close_gpio(fd);
}

static int _set_gpio_output(struct gpio_sysfs *sysfs, int pin)
{
    if (sysfs == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    if (pin < 0 || pin >= TOTAL_GPIO)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pin range.\n");
        return -EPERM;
    }

    struct gpio_ctrl *ctrl = &sysfs->ctrl[pin];
    int real = sysfs->base + pin;
    char path[128] = {
        0,
    };

    snprintf(path, sizeof(path), "%s/gpio%d", GPIO_CLASS_PATH, real);
    if (access(path, F_OK) != 0)
    {
        char real_port[128] = {
            0,
        };
        snprintf(real_port, sizeof(real_port), "%d", real);
        write(sysfs->export, real_port, strlen(real_port));

        ctrl->direction = _init_gpio_direction(real);
        if (ctrl->direction < 0)
            return -EPERM;

        ctrl->value = _init_gpio_value(real);
        if (ctrl->value < 0)
            return -EPERM;
    }

    if (ctrl->direction > 0)
        write(ctrl->direction, "out", 3);

    return 0;
}

static int _write_gpio(struct gpio_sysfs *sysfs, int pin, int value)
{
    if (sysfs == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    if (pin < 0 || pin >= TOTAL_GPIO)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pin range.\n");
        return -EPERM;
    }

    struct gpio_ctrl *ctrl = &sysfs->ctrl[pin];
    if (ctrl->direction < 0 || ctrl->value < 0)
    {
        fprintf(stderr, "[JCRT ERR] Invalid file descriptor.\n");
        return -EPERM;
    }

    write(ctrl->value, value ? "1" : "0", 1);

    return 0;
}

static void _handler_for_ctrl_c(int signo)
{
    (void)signo;

    g_escape = ON;
}

static inline int _get_base_num(const char *str)
{
    int num;
    int ret = sscanf(str, "gpiochip%d", &num);
    if (ret != 1)
    {
        fprintf(stderr, "[JCRT ERR] Failed to get base number.\n");
        return -EPERM;
    }

    return num;
}

static inline int _open_gpio(const char *path)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        fprintf(stderr, "[JCRT ERR] Failed to open file: %s\n", path);
        return -EPERM;
    }

    return fd;
}

static inline int _close_gpio(int fd)
{
    if (fd <= 0)
    {
        fprintf(stderr, "[JCRT ERR] Invalid file descriptor.\n");
        return -EPERM;
    }

    close(fd);

    return 0;
}

static inline int _check_permission(void)
{
    if (getuid() == 0 || geteuid() == 0)
        return 0;

    return -EPERM;
}
