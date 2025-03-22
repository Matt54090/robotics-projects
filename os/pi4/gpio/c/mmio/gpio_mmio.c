/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <signal.h>
#include <stdint.h>
#include <sys/mman.h>

#include <jcrt/common.h>

#define DEBUG

enum {
    BLOCK_SIZE = 4096,
};

struct gpio_mmio {
    int fd;
    volatile uint32_t *base;
};

static struct gpio_mmio *_init_gpio(void);
static int _exit_gpio(struct gpio_mmio *del);

static int _set_gpio_output(struct gpio_mmio *mmio, int pin);
static int _write_gpio(struct gpio_mmio *mmio, int pin, int value);

int main(void)
{
    FORMULA_GUARD(check_permission() < 0, -EPERM, "Need to execute as root!");

    struct sigaction sig_act = {
        .sa_handler = handler_for_ctrl_c,
        .sa_flags = 0,
    };
    sigemptyset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);

    struct gpio_mmio *mmio = _init_gpio();
    FORMULA_GUARD(mmio == NULL, -EPERM, "");

    _set_gpio_output(mmio, IO_PORT);

    while (g_escape == OFF)
    {
        _write_gpio(mmio, IO_PORT, ON);
        DBG_MSG("GPIO set!");
        sleep(1);

        _write_gpio(mmio, IO_PORT, OFF);
        DBG_MSG("GPIO clear.");
        sleep(1);
    }

    _write_gpio(mmio, IO_PORT, OFF);
    _exit_gpio(mmio);
    DBG_MSG("Exit the gpio_mmio.c");

    return 0;
}

static struct gpio_mmio *_init_gpio(void)
{
    struct gpio_mmio *new = malloc(sizeof(struct gpio_mmio));
    FORMULA_GUARD(new == NULL, NULL, ERR_MEMORY_SHORTAGE);

    memset(new, 0x0, sizeof(struct gpio_mmio));

    new->fd = open("/dev/mem", O_RDWR | O_SYNC);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->fd < 0, NULL, _exit_gpio(new),
                                 "Failed to open /dev/mem.");

    new->base =
        (volatile uint32_t *)mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED, new->fd, GPIO_BASE_ADDR);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->base == MAP_FAILED, NULL, _exit_gpio(new),
                                 "Failed to map GPIO registers.");

    return new;
}

static int _exit_gpio(struct gpio_mmio *del)
{
    FORMULA_GUARD(del == NULL, -EPERM, ERR_INVALID_PTR);

    if (del->base)
        munmap((void *)del->base, BLOCK_SIZE);

    if (del->fd)
        close(del->fd);

    PTR_FREE(del);

    return 0;
}

static int _set_gpio_output(struct gpio_mmio *mmio, int pin)
{
    FORMULA_GUARD(mmio == NULL || mmio->base == NULL, -EPERM, ERR_INVALID_PTR);

    int idx = pin / 10;
    int offset = (pin % 10) * 3;

    mmio->base[idx] &= ~(0x7 << offset);
    mmio->base[idx] |= (0x1 << offset);

    return 0;
}

static int _write_gpio(struct gpio_mmio *mmio, int pin, int value)
{
    FORMULA_GUARD(mmio == NULL || mmio->base == NULL, -EPERM, ERR_INVALID_PTR);

    uint32_t mode = ((value == ON) ? GPIO_GPSET0 : GPIO_GPCLR0) >> 2;
    mmio->base[mode] = 1 << pin;

    return 0;
}
