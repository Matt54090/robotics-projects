/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_uart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static dev_uart_ctx_t *g_dev_ctx;

void dev_uart_init(dev_uart_ctx_t *ctx)
{
    memset(ctx, 0x0, sizeof(dev_uart_ctx_t));

    bsp_uart_init(&ctx->bsp);

    g_dev_ctx = ctx;
}

void dev_uart_send(dev_uart_ctx_t *ctx, uint8_t *data, uint16_t len)
{
    while (bsp_uart_is_tx_busy(&ctx->bsp) == STATUS_BUSY)
        ;

    bsp_uart_transmit(&ctx->bsp, data, len);
}

int dev_printf(const char *fmt, ...)
{
    if (g_dev_ctx == NULL)
        return -1;

    dev_uart_ctx_t *ctx = g_dev_ctx;

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(ctx->buf, sizeof(ctx->buf), fmt, args);
    va_end(args);

    if (len <= 0)
        return len;

    int send_len = len;
    if (send_len >= UART_BUF_SIZE)
        send_len = UART_BUF_SIZE;

    dev_uart_send(ctx, (uint8_t *)ctx->buf, send_len);
    return send_len;
}

uint32_t dev_time_get_tick(void)
{
    return bsp_time_get_tick();
}
