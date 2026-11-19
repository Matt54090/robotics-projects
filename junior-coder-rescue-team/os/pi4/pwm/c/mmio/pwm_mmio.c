/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <stdint.h>
#include <sys/mman.h>

#include <jcrt/common.h>

#define PLLD_CLK 750000000.0 // 750 MHz
#define PWM_CLK_HZ 1000.0    // 1 kHz
#define PWM_RANGE 1000

struct pwm_mmio {
    int fd;
    long page_size;

    volatile uint32_t *gpio;
    volatile uint32_t *base;
    volatile uint32_t *clk;
};

static struct pwm_mmio *_init_pwm(void);
static int _exit_pwm(struct pwm_mmio *del);

static int _set_gpio_config(volatile uint32_t *gpio);
static int _clear_gpio_config(volatile uint32_t *gpio);

static int _set_pwm_config(volatile uint32_t *base, volatile uint32_t *clk,
                           uint32_t pwm_clk_hz);
static int _clear_pwm_config(volatile uint32_t *base, volatile uint32_t *clk);

static inline void _compute_divisor(double src_hz, double pwm_clk_hz,
                                    uint32_t *divi, uint32_t *divf);

int main(void)
{
    int ret = init_jcrt();
    FORMULA_GUARD(ret < 0, ret, "Failed to initialize jcrt.");

    struct pwm_mmio *pwm = _init_pwm();
    FORMULA_GUARD(pwm == NULL, -EPERM, "");

    uint32_t duty;
    while (g_escape == OFF)
    {
        /* change the duty cycle from 0 to 1,000,000 */
        for (int i = 0; i < 10; i++)
        {
            if (g_escape == ON)
                break;

            duty = (uint32_t)((i * PWM_RANGE) / 10);
            _write_to_reg(pwm->base, PWM_DAT1, duty);
            DBG_MSG("Set PWM duty cycle to %d", (uint32_t)(i * 100000));
            sleep(1);
        }

        /* change the duty cycle from 1,000,000 to 0 */
        for (int i = 10; i >= 0; i--)
        {
            if (g_escape == ON)
                break;

            duty = (uint32_t)((i * PWM_RANGE) / 10);
            _write_to_reg(pwm->base, PWM_DAT1, duty);
            DBG_MSG("Set PWM duty cycle to %d", (uint32_t)(i * 100000));
            sleep(1);
        }
    }

    _exit_pwm(pwm);
    DBG_MSG("Exit the pwm_mmio.c");

    return 0;
}

static struct pwm_mmio *_init_pwm(void)
{
    struct pwm_mmio *new = malloc(sizeof(struct pwm_mmio));
    FORMULA_GUARD_WITH_EXIT_FUNC(new == NULL, NULL, _exit_pwm(new),
                                 ERR_MEMORY_SHORTAGE);

    new->fd = open("/dev/mem", O_RDWR | O_SYNC);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->fd < 0, NULL, _exit_pwm(new),
                                 "Failed to open /dev/mem.");

    new->page_size = sysconf(_SC_PAGE_SIZE);
    new->gpio = mmap(NULL, new->page_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                     new->fd, GPIO_BASE_ADDR);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->gpio == MAP_FAILED, NULL, _exit_pwm(new),
                                 "Failed to map GPIO base address.");

    new->base = mmap(NULL, new->page_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                     new->fd, PWM_BASE_ADDR);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->base == MAP_FAILED, NULL, _exit_pwm(new),
                                 "Failed to map PWM base address.");

    new->clk = mmap(NULL, new->page_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                    new->fd, CLK_BASE_ADDR);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->clk == MAP_FAILED, NULL, _exit_pwm(new),
                                 "Failed to map Clock base address.");

    _set_gpio_config(new->gpio);
    _set_pwm_config(new->base, new->clk, (uint32_t)(PWM_CLK_HZ * PWM_RANGE));

    return new;
}

static int _exit_pwm(struct pwm_mmio *del)
{
    FORMULA_GUARD(del == NULL, -EPERM, ERR_INVALID_PTR);

    g_escape = ON;

    _clear_pwm_config(del->base, del->clk);
    _clear_gpio_config(del->gpio);

    if (del->clk)
        munmap((void *)del->clk, del->page_size);

    if (del->base)
        munmap((void *)del->base, del->page_size);

    if (del->gpio)
        munmap((void *)del->gpio, del->page_size);

    if (del->fd >= 0)
        close(del->fd);

    PTR_FREE(del);

    return 0;
}

static int _set_gpio_config(volatile uint32_t *gpio)
{
    FORMULA_GUARD(gpio == NULL, -EPERM, ERR_INVALID_PTR);

    /* set GPIO to ALT5 */
    _read_modify_write(gpio, GPFSEL1, (0x7u << 24), (0x2u << 24));

    return 0;
}

static int _clear_gpio_config(volatile uint32_t *gpio)
{
    FORMULA_GUARD(gpio == NULL, -EPERM, ERR_INVALID_PTR);

    /* set GPIO to INPUT */
    _read_modify_write(gpio, GPFSEL1, (0x7u << 24), (0x0u << 24));

    return 0;
}

static int _set_pwm_config(volatile uint32_t *base, volatile uint32_t *clk,
                           uint32_t pwm_clk_hz)
{
    FORMULA_GUARD(base == NULL || clk == NULL, -EPERM, ERR_INVALID_PTR);

    /* stop PWM */
    _write_to_reg(base, PWM_CTL, 0x0);
    _busy_wait(10);

    /* kill the clock */
    _write_to_reg(clk, CM_PWMCTL, (0x5au << 24) | (0x1u << 5));
    _busy_wait(110);

    /* wait BUSY clear */
    while (_read_from_reg(clk, CM_PWMCTL) & (0x1u << 7))
        _busy_wait(10);

    /* choose plld(750MHz) as source and compute divisor */
    uint32_t divi, divf;
    _compute_divisor(PLLD_CLK, (double)pwm_clk_hz, &divi, &divf);
    _write_to_reg(clk, CM_PWMDIV,
                  (0x5au << 24) | (divi << 12) | (divf & 0xfff));
    _write_to_reg(clk, CM_PWMCTL, (0x5au << 24) | (6 & 0xf) | (0x1u << 4));
    _busy_wait(110);

    /* status clear */
    _write_to_reg(base, PWM_STA, 0x0F);
    _busy_wait(10);

    /* period ticks */
    _write_to_reg(base, PWM_RNG1, PWM_RANGE);
    _busy_wait(10);

    /* mark-space, enable */
    _write_to_reg(base, PWM_CTL, (0x1u << 7) | (0x1u << 0));

    return 0;
}

static int _clear_pwm_config(volatile uint32_t *base, volatile uint32_t *clk)
{
    FORMULA_GUARD(base == NULL || clk == NULL, -EPERM, ERR_INVALID_PTR);

    /* stop PWM */
    _write_to_reg(base, PWM_CTL, 0x0);
    _busy_wait(10);

    /* clear FIFO */
    _write_to_reg(base, PWM_CTL, (0x1u << 6) | (0x1u << 5));

    /* kill the clock */
    _write_to_reg(clk, CM_PWMCTL, (0x5au << 24) | (0x1u << 5));
    _busy_wait(110);

    /* wait BUSY clear */
    while (_read_from_reg(clk, CM_PWMCTL) & (0x1u << 7))
        _busy_wait(10);

    return 0;
}

static inline void _compute_divisor(double src_hz, double pwm_clk_hz,
                                    uint32_t *divi, uint32_t *divf)
{
    double div = src_hz / pwm_clk_hz;

    /* minimum */
    if (div < 1.0)
        div = 1.0;

    /* resolution is 12bit */
    if (div > 4095.999)
        div = 4095.999;

    /* integer */
    *divi = (uint32_t)div;

    /* fractional */
    *divf = (uint32_t)((div - *divi) * 4096.0 + 0.5);
}
