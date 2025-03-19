/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum {
    OFF,
    ON
};

enum gpio_info_e {
    PI4_GPIO_BASE = 0xFE200000,
    PI4_GPIO_GPSET0 = 0x1c,
    PI4_GPIO_GPCLR0 = 0x28,

    BLOCK_SIZE = 4096,
    IO_PORT = 18,
};

struct gpio_mmio {
    int fd;
    volatile uint32_t *base;
};

static struct gpio_mmio *_init_gpio(void);
static int _exit_gpio(struct gpio_mmio *del);

static int _set_gpio_output(struct gpio_mmio *mmio, int pin);
static int _write_gpio(struct gpio_mmio *mmio, int pin, int value);

static void _handler_for_ctrl_c(int signo);
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

    struct gpio_mmio *mmio = _init_gpio();
    if (mmio == NULL)
        return -EPERM;

    _set_gpio_output(mmio, IO_PORT);

    while (g_escape == OFF)
    {
        _write_gpio(mmio, IO_PORT, ON);
        printf("[JCRT] GPIO set!\n");
        sleep(1);

        _write_gpio(mmio, IO_PORT, OFF);
        printf("[JCRT] GPIO clear.\n");
        sleep(1);
    }

    _write_gpio(mmio, IO_PORT, OFF);
    _exit_gpio(mmio);
    printf("[JCRT] Exit the gpio_mmio.c\n");

    return 0;
}

static struct gpio_mmio *_init_gpio(void)
{
    struct gpio_mmio *new = malloc(sizeof(struct gpio_mmio));
    if (new == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Memory allocation failed.\n");
        return NULL;
    }

    memset(new, 0x0, sizeof(struct gpio_mmio));

    new->fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (new->fd < 0)
    {
        fprintf(stderr, "[JCRT ERR] Failed to open /dev/mem.\n");
        _exit_gpio(new);
        return NULL;
    }

    new->base =
        (volatile uint32_t *)mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, new->fd, PI4_GPIO_BASE);
    if (new->base == MAP_FAILED)
    {
        fprintf(stderr, "[JCRT ERR] Failed to map GPIO registers.\n");
        _exit_gpio(new);
        return NULL;
    }

    return new;
}

static int _exit_gpio(struct gpio_mmio *del)
{
    if (del == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    if (del->base)
        munmap((void *)del->base, BLOCK_SIZE);

    if (del->fd)
        close(del->fd);

    free(del);
    del = NULL;

    return 0;
}

static int _set_gpio_output(struct gpio_mmio *mmio, int pin)
{
    if (mmio == NULL || mmio->base == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    int idx = pin / 10;
    int offset = (pin % 10) * 3;

    mmio->base[idx] &= ~(0x7 << offset);
    mmio->base[idx] |= (0x1 << offset);

    return 0;
}

static int _write_gpio(struct gpio_mmio *mmio, int pin, int value)
{
    if (mmio == NULL || mmio->base == NULL)
    {
        fprintf(stderr, "[JCRT ERR] Invalid pointer.\n");
        return -EPERM;
    }

    uint32_t mode = ((value == ON) ? PI4_GPIO_GPSET0 : PI4_GPIO_GPCLR0) >> 2;
    mmio->base[mode] = 1 << pin;

    return 0;
}

static void _handler_for_ctrl_c(int signo)
{
    (void)signo;

    g_escape = ON;
}

static inline int _check_permission(void)
{
    if (getuid() == 0 || geteuid() == 0)
        return 0;

    return -EPERM;
}
