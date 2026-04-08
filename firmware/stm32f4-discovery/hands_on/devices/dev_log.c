/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "bsp/bsp_uart.h"

#define UART_BUF_SIZE 128

typedef struct {
    bsp_uart_ctx_t bsp;

    char buf[UART_BUF_SIZE];
} dev_log_ctx_t;

static dev_log_ctx_t g_dev_ctx;

void dev_log_init(void)
{
    dev_log_ctx_t *ctx = &g_dev_ctx;

    memset(ctx, 0x0, sizeof(dev_log_ctx_t));

    bsp_uart_init(&ctx->bsp);
}

int dev_log_send(uint8_t *data, uint16_t len)
{
    dev_log_ctx_t *ctx = &g_dev_ctx;

    while (bsp_uart_is_tx_busy(&ctx->bsp) == STATUS_BUSY)
        ;

    bsp_uart_transmit(&ctx->bsp, data, len);
    bsp_delay_ms(1);

    return 0;
}

int dev_printf(const char *fmt, ...)
{
    dev_log_ctx_t *ctx = &g_dev_ctx;

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(ctx->buf, sizeof(ctx->buf), fmt, args);
    va_end(args);

    if (len <= 0)
        return len;

    int send_len = len;
    if (send_len >= UART_BUF_SIZE)
        send_len = UART_BUF_SIZE;

    dev_log_send((uint8_t *)ctx->buf, send_len);
    return send_len;
}

int dev_protocol_send(protocol_e type, uint32_t data)
{
    dev_log_ctx_t *ctx = &g_dev_ctx;

    uint8_t buf[8];

    buf[0] = 0xAA;
    buf[1] = type;

    buf[2] = (data >> 24) & 0xFF;
    buf[3] = (data >> 16) & 0xFF;
    buf[4] = (data >> 8) & 0xFF;
    buf[5] = data & 0xFF;

    buf[6] = buf[1] ^ buf[2] ^ buf[3] ^ buf[4] ^ buf[5];
    buf[7] = 0x55;

    bsp_uart_transmit(&ctx->bsp, buf, sizeof(buf));

    return 0;
}
