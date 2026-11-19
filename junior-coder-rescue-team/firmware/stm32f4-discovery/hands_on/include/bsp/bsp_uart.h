/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_UART_H
#define BSP_UART_H

#include <stdint.h>

#include "common/board_config.h"
#include "common/common_hands_on.h"

typedef enum {
    STATUS_BUSY = -2,
    STATUS_ERROR,
    STATUS_SUCCESS,
    STATUS_IDLE = 0,
    STATUS_READY
} status_e;

typedef struct {
    UART_HandleTypeDef *huart;

    status_e tx_busy;
} bsp_uart_ctx_t;

void bsp_uart_init(bsp_uart_ctx_t *ctx);
int bsp_uart_transmit(bsp_uart_ctx_t *ctx, uint8_t *data, uint16_t len);
int bsp_uart_is_tx_busy(bsp_uart_ctx_t *ctx);

#endif /* BSP_UART_H */
