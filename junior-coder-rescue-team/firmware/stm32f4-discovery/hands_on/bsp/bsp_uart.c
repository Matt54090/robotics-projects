/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_uart.h"

#include <stddef.h>

#include "common/common_hands_on.h"

static bsp_uart_ctx_t *g_bsp_uart_ctx;

void bsp_uart_init(bsp_uart_ctx_t *ctx)
{
    ctx->huart = &huart2;
    ctx->tx_busy = STATUS_IDLE;

    g_bsp_uart_ctx = ctx;
}

int bsp_uart_transmit(bsp_uart_ctx_t *ctx, uint8_t *data, uint16_t len)
{
    if (ctx->tx_busy == STATUS_BUSY)
        return RETURN_BUSY;

    ctx->tx_busy = STATUS_BUSY;

    if (HAL_UART_Transmit_IT(ctx->huart, data, len) != HAL_OK)
    {
        ctx->tx_busy = STATUS_IDLE;
        return RETURN_ERROR;
    }

    return 0;
}

int bsp_uart_is_tx_busy(bsp_uart_ctx_t *ctx)
{
    return (ctx->tx_busy == STATUS_BUSY) ? RETURN_BUSY : RETURN_OK;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    (void)huart;

    bsp_uart_ctx_t *ctx = g_bsp_uart_ctx;
    if (ctx == NULL)
        return;

    ctx->tx_busy = STATUS_IDLE;
}
