/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_UART_H
#define DEV_UART_H

#include <stdint.h>

#include "bsp_uart.h"

#define UART_BUF_SIZE 128

typedef struct {
    bsp_uart_ctx_t bsp;

    char buf[UART_BUF_SIZE];
} dev_uart_ctx_t;

void dev_uart_init(dev_uart_ctx_t *ctx);
void dev_uart_send(dev_uart_ctx_t *ctx, uint8_t *data, uint16_t len);
int dev_printf(const char *fmt, ...);

uint32_t dev_time_get_tick(void);

#endif
