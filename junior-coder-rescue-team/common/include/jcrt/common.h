/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:ffs=unix */
#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR_INVALID_PTR "Invalid Pointer."
#define ERR_INVALID_RET "Invalild return value."
#define ERR_INVALID_FD "Invalid File Descripter."
#define ERR_INVALID_PARAMS "Invalid Parameters."
#define ERR_MEMORY_SHORTAGE "Failed to allocate the memory."

#define unlikely(x) __builtin_expect(!!(x), 0)

#ifdef DEBUG
#define DBG_MSG(fmt, ...)                                                      \
    do                                                                         \
    {                                                                          \
        printf("[JCRT] " fmt " / func : %s, line : %d\n", ##__VA_ARGS__,       \
               __func__, __LINE__);                                            \
    } while (0)
#else
#define DBG_MSG(fmt, ...)                                                      \
    do                                                                         \
    {                                                                          \
    } while (0)
#endif

#define ERR_MSG(fmt, ...)                                                      \
    do                                                                         \
    {                                                                          \
        fprintf(stderr, "[JCRT ERR] " fmt " / func : %s, line : %d\n",         \
                ##__VA_ARGS__, __func__, __LINE__);                            \
    } while (0)

#define FORMULA_GUARD(formula, ret, msg, ...)                                  \
    do                                                                         \
    {                                                                          \
        if (unlikely(formula))                                                 \
        {                                                                      \
            if (strcmp(msg, ""))                                               \
                ERR_MSG(msg, ##__VA_ARGS__);                                   \
            return ret;                                                        \
        }                                                                      \
    } while (0)

#define FORMULA_GUARD_WITH_EXIT_FUNC(formula, ret, func, msg, ...)             \
    do                                                                         \
    {                                                                          \
        if (unlikely(formula))                                                 \
        {                                                                      \
            if (strcmp(msg, ""))                                               \
                ERR_MSG(msg, ##__VA_ARGS__);                                   \
            return func, ret;                                                  \
        }                                                                      \
    } while (0)

#define PTR_FREE(ptr)                                                          \
    do                                                                         \
    {                                                                          \
        if (ptr)                                                               \
        {                                                                      \
            free(ptr);                                                         \
            ptr = NULL;                                                        \
        }                                                                      \
    } while (0)

enum {
    OFF,
    ON,

    TIMEOUT = 1000,
    BLOCK_SIZE = 4096,
};

enum gpio_info_e {
    GPIO_BASE_ADDR = 0xfe200000,
    GPIO_GPSET0 = 0x1c,
    GPIO_GPCLR0 = 0x28,

    GPFSEL1 = 0x04,
    GPPUPPDN0 = 0xe4,

    IO_PORT = 18,

    TOTAL_GPIO = 58
};

enum uart_info_e {
    UART_BASE_ADDR = 0xfe201400, /* UART2 */
    UART_DR = 0x00,
    UART_FR = 0x18,
    UART_IBRD = 0x24,
    UART_FBRD = 0x28,
    UART_LCRH = 0x2c,
    UART_CR = 0x30,
    UART_ICR = 0x44,
};

enum pwm_info_e {
    PWM_BASE_ADDR = 0xfe20c000, /* PWM0 */
    PWM_CTL = 0x00,
    PWM_STA = 0x04,
    PWM_DMAC = 0x08,
    PWM_RNG1 = 0x10,
    PWM_DAT1 = 0x14,
    PWM_FIF1 = 0x18,
    PWM_RNG2 = 0x20,
    PWM_DAT2 = 0x24,

    CLK_BASE_ADDR = 0xfe101000, /* Clock */
    CM_PWMCTL = 0xa0,
    CM_PWMDIV = 0xa4,
};

static inline int init_jcrt(void);
static inline void handler_for_ctrl_c(int signo);
static inline int check_permission(void);

int g_escape = OFF;

static inline int init_jcrt(void)
{
    int ret = check_permission();
    FORMULA_GUARD(ret < 0, -EPERM, ERR_INVALID_RET);

    struct sigaction sig_act = {
        .sa_handler = handler_for_ctrl_c,
        .sa_flags = 0,
    };

    ret = sigemptyset(&sig_act.sa_mask);
    FORMULA_GUARD(ret < 0, -EPERM, ERR_INVALID_RET);

    ret = sigaction(SIGINT, &sig_act, NULL);
    FORMULA_GUARD(ret < 0, -EPERM, ERR_INVALID_RET);

    return 0;
}

static inline void handler_for_ctrl_c(int signo)
{
    (void)signo;

    g_escape = ON;
}

static inline int check_permission(void)
{
    if (getuid() == 0 || geteuid() == 0)
        return 0;

    return -EPERM;
}

static inline uint32_t _set_bits(uint32_t base, int set)
{
    return base |= set;
}

static inline uint32_t _clear_bits(uint32_t base, int clear)
{
    return base &= ~(clear);
}

static inline void _write_to_reg(volatile uint32_t *base, int offset, int value)
{
    base[offset >> 2] = value;
}

static inline uint32_t _read_from_reg(const volatile uint32_t *base, int offset)
{
    return base[offset >> 2];
}

static inline void _read_modify_write(volatile uint32_t *base, int offset,
                                      uint32_t clear, uint32_t set)
{
    uint32_t value = _read_from_reg(base, offset);
    value = _clear_bits(value, clear);
    value = _set_bits(value, set);
    _write_to_reg(base, offset, value);
}

static inline void _busy_wait(int us)
{
    usleep(us);
}

#endif /* COMMON_H */
