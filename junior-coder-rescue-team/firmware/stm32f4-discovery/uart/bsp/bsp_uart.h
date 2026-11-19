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

#include "common_uart.h"

#ifdef UNIT_TEST
#include "board_uart_config.h"
#else
#include "stm32f4xx_hal.h"
#include "usart.h"
#endif

typedef struct {
    UART_HandleTypeDef *huart;

    status_e tx_busy;
} bsp_uart_ctx_t;

void bsp_uart_init(bsp_uart_ctx_t *ctx);
status_e bsp_uart_transmit(bsp_uart_ctx_t *ctx, uint8_t *data, uint16_t len);
status_e bsp_uart_is_tx_busy(bsp_uart_ctx_t *ctx);

uint32_t bsp_uart_time_get_tick(void);
void bsp_uart_delay_ms(uint32_t ms);

#endif /* BSP_UART_H */
