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

#include "common/common_hands_on.h"

void dev_log_init(void);
int dev_log_send(uint8_t *data, uint16_t len);

int dev_printf(const char *fmt, ...);
int dev_protocol_send(protocol_e type, uint32_t data);

#endif
