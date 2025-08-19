#include <pthread.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>

#include <jcrt/common.h>

struct uart_mmio {
    int fd;
    size_t span;
    volatile uint32_t *base;
    volatile uint32_t *mmap_base;

    pthread_t ts_th;
    pthread_t rs_th;
};

static struct uart_mmio *_init_uart(void);
static int _exit_uart(struct uart_mmio *del);

static int _set_uart_config(volatile uint32_t *base);

static void *_transmitter(void *arg);
static void *_receiver(void *arg);

int main(void)
{
    int ret = init_jcrt();
    FORMULA_GUARD(ret < 0, ret, "Failed to initialize jcrt");

    struct uart_mmio *uart = _init_uart();
    FORMULA_GUARD(uart == NULL, -EPERM, "");

    while (g_escape == OFF)
    {
        sleep(1);
    }

    _exit_uart(uart);
    DBG_MSG("Exit the uart_mmio.c");

    return 0;
}

static struct uart_mmio *_init_uart(void)
{
    struct uart_mmio *new = malloc(sizeof(struct uart_mmio));
    FORMULA_GUARD(new == NULL, NULL, ERR_MEMORY_SHORTAGE);

    new->fd = open("/dev/mem", O_RDWR | O_SYNC);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->fd < 0, NULL, _exit_uart(new),
                                 "Failed to open /dev/mem.");

    long pagesz = sysconf(_SC_PAGESIZE);
    off_t aligned = UART_BASE_ADDR & ~((off_t)pagesz - 1);
    off_t delta = UART_BASE_ADDR - aligned;
    new->span =
        ((size_t)delta + BLOCK_SIZE + pagesz - 1) & ~((size_t)pagesz - 1);

    void *ptr = mmap(NULL, new->span, PROT_READ | PROT_WRITE, MAP_SHARED,
                     new->fd, aligned);
    FORMULA_GUARD_WITH_EXIT_FUNC(new->base == MAP_FAILED, NULL, _exit_uart(new),
                                 "Failed to map UART base address.");

    new->mmap_base = ptr;
    new->base = (volatile uint32_t *)((uint8_t *)ptr + delta);

    _set_uart_config(new->base);

    int ret =
        pthread_create(&new->ts_th, NULL, _transmitter, (void *)new->base);
    FORMULA_GUARD_WITH_EXIT_FUNC(ret != 0, NULL, _exit_uart(new),
                                 "Failed to create TX thread.");

    ret = pthread_create(&new->rs_th, NULL, _receiver, (void *)new->base);
    FORMULA_GUARD_WITH_EXIT_FUNC(ret != 0, NULL, _exit_uart(new),
                                 "Failed to create RX thread.");

    return new;
}

static int _exit_uart(struct uart_mmio *del)
{
    FORMULA_GUARD(del == NULL, -EPERM, ERR_INVALID_PTR);

    g_escape = ON;

    pthread_join(del->rs_th, NULL);
    pthread_join(del->ts_th, NULL);

    if (del->mmap_base)
        munmap((void *)del->mmap_base, del->span);

    if (del->fd >= 0)
        close(del->fd);

    PTR_FREE(del);

    return 0;
}

static int _set_uart_config(volatile uint32_t *base)
{
    FORMULA_GUARD(base == NULL, -EPERM, ERR_INVALID_PTR);

    /* disable the UART for the setting up */
    _write_to_reg(base, UART_CR, 0x0);

    /* wait for the UART to be ready */
    while (_read_from_reg(base, UART_FR) & (0x1u << 3))
        _busy_wait(100);

    /* clear the interrupt */
    _write_to_reg(base, UART_ICR, 0x7ff);

    /*
     * set the baudrate as 115200
     * UART CLK = 48MHz
     * Baud Div = UART CLK / (16 * Baud)
     *           48,000,000 / (16 * 115200) ≈ 26.041666
     */
    const unsigned int ibrd = 26;
    const unsigned int fbrd = (const unsigned int)(0.041666 * 64 + 0.5);
    _write_to_reg(base, UART_IBRD, ibrd);
    _write_to_reg(base, UART_FBRD, fbrd);

    /* 8 data bit, no parity, 1 stop bit, FIFO enable */
    _write_to_reg(base, UART_LCRH, (0x3u << 5) | (0x1u << 4));

    /* no flow control and TX/RX enable and enable the UART */
    _read_modify_write(base, UART_CR, (0x1u << 15) | (0x1u << 14),
                       (0x1u << 9) | (0x1u << 8) | 0x1);

    return 0;
}

static void *_transmitter(void *arg)
{
    volatile uint32_t *base = (volatile uint32_t *)arg;
    char buf[256] = {
        0,
    };

    int len;
    const int size = sizeof(buf);

    fd_set read_fds;
    struct timeval timeout;

    while (g_escape == OFF)
    {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        /* for checking the ctrl + c */
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;
        int ret = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(STDIN_FILENO, &read_fds))
        {
            if (!fgets(buf, size, stdin))
                break;

            len = strlen(buf);
            for (int i = 0; i < len; i++)
            {
                /* check the TX buffer */
                while (_read_from_reg(base, UART_FR) & (0x1u << 5))
                {
                    if (g_escape == ON)
                        return NULL;

                    _busy_wait(100);
                }
                _write_to_reg(base, UART_DR, (uint8_t)buf[i]);
            }
            DBG_MSG("TX: %s", buf);
        }
    }

    DBG_MSG("Exiting transmitter thread.");
    return NULL;
}

static void *_receiver(void *arg)
{
    const volatile uint32_t *base = (const volatile uint32_t *)arg;
    char buf[256] = {
        0,
    };

    char ret;
    int index = 0;
    const int size = sizeof(buf);
    while (g_escape == OFF)
    {
        /* check the RX buffer */
        if (_read_from_reg(base, UART_FR) & (0x1u << 4))
            continue;

        ret = _read_from_reg(base, UART_DR) & 0xff;
        if (ret == '\r' || index >= size - 1)
        {
            buf[index] = '\0';
            index = 0;
            DBG_MSG("RX: %s", buf);
        }
        else
            buf[index++] = ret;

        _busy_wait(100);
    }

    DBG_MSG("Exiting receiver thread.");
    return NULL;
}
