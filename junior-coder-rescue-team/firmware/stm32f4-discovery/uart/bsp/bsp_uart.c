/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_uart.h"

#include <stddef.h>

static bsp_uart_ctx_t *g_bsp_uart_ctx;

void bsp_uart_init(bsp_uart_ctx_t *ctx)
{
    ctx->huart = &huart2;
    ctx->tx_busy = STATUS_IDLE;

    g_bsp_uart_ctx = ctx;
}

status_e bsp_uart_transmit(bsp_uart_ctx_t *ctx, uint8_t *data, uint16_t len)
{
    if (ctx->tx_busy == STATUS_BUSY)
        return STATUS_BUSY;

    ctx->tx_busy = STATUS_BUSY;

    if (HAL_UART_Transmit_IT(ctx->huart, data, len) != HAL_OK)
    {
        ctx->tx_busy = STATUS_IDLE;
        return STATUS_ERROR;
    }

    return STATUS_SUCCESS;
}

status_e bsp_uart_is_tx_busy(bsp_uart_ctx_t *ctx)
{
    return (ctx->tx_busy == STATUS_BUSY) ? STATUS_BUSY : STATUS_IDLE;
}

uint32_t bsp_uart_time_get_tick(void)
{
    return HAL_GetTick();
}

void bsp_uart_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    (void)huart;

    bsp_uart_ctx_t *ctx = g_bsp_uart_ctx;
    if (ctx == NULL)
        return;

    ctx->tx_busy = STATUS_IDLE;
}
