/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <dirent.h>
#include <math.h>
#include <signal.h>

#include <jcrt/common.h>

#define GPIO_BASE_PATH "/sys/devices/platform/soc"
#define GPIO_CLASS_PATH "/sys/class/gpio"

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

static inline int _get_base_num(const char *str);

static inline int _open_gpio(const char *path);
static inline int _close_gpio(int fd);

int main(void)
{
    FORMULA_GUARD(check_permission() < 0, -EPERM, "Need to execute as root!");

    struct sigaction sig_act = {
        .sa_handler = handler_for_ctrl_c,
        .sa_flags = 0,
    };
    sigemptyset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);

    struct gpio_sysfs *gpio = _init_gpio();
    FORMULA_GUARD(gpio == NULL, -EPERM, "");

    int ret = _set_gpio_output(gpio, IO_PORT);
    if (ret == 0)
    {
        while (g_escape == OFF)
        {
            _write_gpio(gpio, IO_PORT, ON);
            DBG_MSG("GPIO set!");
            sleep(1);

            _write_gpio(gpio, IO_PORT, OFF);
            DBG_MSG("GPIO clear.");
            sleep(1);
        }
    }

    _exit_gpio(gpio);
    DBG_MSG("Exit the gpio_sysfs.c");

    return 0;
}

static struct gpio_sysfs *_init_gpio(void)
{
    struct gpio_sysfs *new = malloc(sizeof(struct gpio_sysfs));
    FORMULA_GUARD(new == NULL, NULL, ERR_MEMORY_SHORTAGE);
    memset(new, 0x0, sizeof(struct gpio_sysfs));

    new->base = _find_gpio_base();
    FORMULA_GUARD_WITH_EXIT_FUNC(new->base < 0, NULL, _exit_gpio(new), "");

    new->export = _init_gpio_export();
    FORMULA_GUARD_WITH_EXIT_FUNC(new->export < 0, NULL, _exit_gpio(new), "");

    new->ctrl = malloc(sizeof(struct gpio_ctrl) * TOTAL_GPIO);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->ctrl == NULL, NULL, _exit_gpio(new), "");
    memset(new->ctrl, 0x0, sizeof(struct gpio_ctrl) * TOTAL_GPIO);

    return new;
}

static int _exit_gpio(struct gpio_sysfs *del)
{
    FORMULA_GUARD(del == NULL, -EPERM, ERR_INVALID_PTR);

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

        PTR_FREE(del->ctrl);
    }

    _exit_gpio_export(del->export);

    PTR_FREE(del);

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
    FORMULA_GUARD(dir == NULL, -EPERM, "Failed to open directory");

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
    FORMULA_GUARD(sysfs == NULL, -EPERM, ERR_INVALID_PTR);
    FORMULA_GUARD(pin < 0 || pin >= TOTAL_GPIO, -EPERM, "Invalid pin range.");

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
    FORMULA_GUARD(sysfs == NULL, -EPERM, ERR_INVALID_PTR);
    FORMULA_GUARD(pin < 0 || pin >= TOTAL_GPIO, -EPERM, "Invalid pin range.");

    struct gpio_ctrl *ctrl = &sysfs->ctrl[pin];
    FORMULA_GUARD(ctrl->direction < 0 || ctrl->value < 0, -EPERM,
                  ERR_INVALID_FD);

    write(ctrl->value, value ? "1" : "0", 1);

    return 0;
}

static inline int _get_base_num(const char *str)
{
    int num;
    int ret = sscanf(str, "gpiochip%d", &num);
    FORMULA_GUARD(ret != 1, -EPERM, "Failed to get base number.");

    return num;
}

static inline int _open_gpio(const char *path)
{
    int fd = open(path, O_WRONLY);
    FORMULA_GUARD(fd < 0, -EPERM, "Failed to open file.");

    return fd;
}

static inline int _close_gpio(int fd)
{
    FORMULA_GUARD(fd <= 0, -EPERM, ERR_INVALID_FD);

    close(fd);

    return 0;
}
