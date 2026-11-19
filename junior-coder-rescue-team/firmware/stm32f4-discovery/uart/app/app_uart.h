/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_UART_H
#define APP_UART_H

#include "dev_uart.h"

typedef struct {
    dev_uart_ctx_t uart;

    uint32_t last_tick;
    uint32_t count;

    char msg[UART_BUF_SIZE];
} app_uart_ctx_t;

void app_uart_init(app_uart_ctx_t *ctx);
void app_uart_run(app_uart_ctx_t *ctx);

#endif
