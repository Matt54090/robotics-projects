/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <libserialport.h>
#include <pthread.h>

#include <jcrt/common.h>

#define UART_DEV "/dev/serial0"

enum uart_info_e {
    TIMEOUT = 0,
};

struct uart_lib {
    pthread_t tx;
    pthread_t rx;

    struct sp_port *sp_port;
};

static struct uart_lib *_init_uart(void);
static int _exit_uart(struct uart_lib *del);

static void *_transmitter(void *arg);
static void *_receiver(void *arg);

int main(void)
{
    int ret = init_jcrt();
    FORMULA_GUARD(ret < 0, ret, "Failed to initialize jcrt.");

    struct uart_lib *uart = _init_uart();
    FORMULA_GUARD(uart == NULL, -EPERM, "");

    while (g_escape == OFF)
    {
        sleep(1);
    }

    _exit_uart(uart);
    DBG_MSG("Exit the uart_lib.c");

    return 0;
}

static struct uart_lib *_init_uart(void)
{
    struct uart_lib *new = malloc(sizeof(struct uart_lib));
    FORMULA_GUARD(new == NULL, NULL, ERR_MEMORY_SHORTAGE);

    enum sp_return sp_ret;
    new->sp_port = NULL;
    sp_ret = sp_get_port_by_name(UART_DEV, &new->sp_port);
    FORMULA_GUARD_WITH_EXIT_FUNC(sp_ret != SP_OK, NULL, _exit_uart(new),
                                 "Failed to get port by name.");

    sp_ret = sp_open(new->sp_port, SP_MODE_READ_WRITE);
    FORMULA_GUARD_WITH_EXIT_FUNC(sp_ret != SP_OK, NULL, _exit_uart(new),
                                 "Failed to open port.");

    sp_set_baudrate(new->sp_port, 115200);
    sp_set_bits(new->sp_port, 8);
    sp_set_parity(new->sp_port, SP_PARITY_NONE);
    sp_set_stopbits(new->sp_port, 1);
    sp_set_flowcontrol(new->sp_port, SP_FLOWCONTROL_NONE);

    int ret = pthread_create(&new->tx, NULL, _transmitter, new->sp_port);
    FORMULA_GUARD_WITH_EXIT_FUNC(ret != 0, NULL, _exit_uart(new),
                                 "Failed to create TX thread.");

    ret = pthread_create(&new->rx, NULL, _receiver, new->sp_port);
    FORMULA_GUARD_WITH_EXIT_FUNC(ret != 0, NULL, _exit_uart(new),
                                 "Failed to create RX thread.");

    return new;
}

static int _exit_uart(struct uart_lib *del)
{
    FORMULA_GUARD(del == NULL, -EPERM, ERR_INVALID_PTR);

    g_escape = ON;

    if (del->rx > 0)
        pthread_join(del->rx, NULL);

    if (del->tx > 0)
        pthread_join(del->tx, NULL);

    if (del->sp_port != NULL)
    {
        sp_close(del->sp_port);
        sp_free_port(del->sp_port);
    }

    PTR_FREE(del);

    return 0;
}

static void *_transmitter(void *arg)
{
    struct sp_port *sp_port = (struct sp_port *)arg;
    char msg[256] = {
        0,
    };

    while (g_escape == OFF)
    {
        printf("Enter the message to send: ");
        fgets(msg, sizeof(msg), stdin);
        sp_blocking_write(sp_port, msg, strlen(msg), TIMEOUT);

        DBG_MSG("TX: %s", msg);
        memset(msg, 0, sizeof(msg));
    }

    DBG_MSG("Exiting transmitter thread.");
    return NULL;
}

static void *_receiver(void *arg)
{
    struct sp_port *sp_port = (struct sp_port *)arg;
    char msg[256] = {
        0,
    };

    while (g_escape == OFF)
    {
        int ret = sp_blocking_read(sp_port, msg, sizeof(msg), TIMEOUT);
        if (ret > 0)
        {
            msg[ret] = '\0';
            DBG_MSG("RX: %s", msg);
        }
    }

    DBG_MSG("Exiting receiver thread.");
    return NULL;
}
