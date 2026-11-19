/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_I2C_MOCK_H
#define HAL_I2C_MOCK_H

#include <stdint.h>

typedef struct {
    int dummy;
} I2C_HandleTypeDef;

#define HAL_MAX_DELAY 0xFFFFFFFF

static inline int HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c,
                                          uint16_t addr, uint8_t *data,
                                          uint16_t size, uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)data;
    (void)size;
    (void)timeout;

    return 0;
}

static inline void HAL_Delay(uint32_t ms)
{
    (void)ms;
}

#endif /* HAL_I2C_MOCK_H */
