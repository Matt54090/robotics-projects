/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_UART_CONFIG_H
#define BOARD_UART_CONFIG_H

#ifdef UNIT_TEST
#include "hal_uart_mock.h"

extern UART_HandleTypeDef huart2;
#else
#include "stm32f4xx_hal.h"
#include "usart.h"

#define BOARD_UART_HANDLE (&huart2)
#endif

#endif /* BOARD_UART_CONFIG_H */
