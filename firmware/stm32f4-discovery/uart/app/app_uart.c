/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_uart.h"

#include <stdio.h>
#include <string.h>

void app_uart_init(app_uart_ctx_t *ctx)
{
    memset(ctx, 0x0, sizeof(app_uart_ctx_t));
    dev_uart_init(&ctx->uart);
}

void app_uart_run(app_uart_ctx_t *ctx)
{
    int len;
    uint32_t now = dev_time_get_tick();

    if (now - ctx->last_tick >= 1000)
    {
        ctx->last_tick = now;
        len = snprintf(ctx->msg, sizeof(ctx->msg), "[STM] alive %lu\r\n",
                       ctx->count++);

        dev_uart_send(&ctx->uart, (uint8_t *)ctx->msg, len);
    }
}