/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_UART_MOCK_H
#define HAL_UART_MOCK_H

#include <stdint.h>

#define HAL_OK 0

typedef struct {
    int dummy;
    void *pUserData;
} UART_HandleTypeDef;

extern UART_HandleTypeDef huart2;

static inline int HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *data,
                                       uint16_t len)
{
    (void)huart;
    (void)data;
    (void)len;

    return HAL_OK;
}

static inline int HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *data,
                                      uint16_t len)
{
    (void)huart;
    (void)data;
    (void)len;

    return HAL_OK;
}

static inline uint32_t HAL_GetTick(void)
{
    return 0;
}

static inline void HAL_Delay(uint32_t ms)
{
    (void)ms;
}

#endif /* HAL_UART_MOCK_H */
