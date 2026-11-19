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

#define I2C_MEMADD_SIZE_8BIT 0x01

typedef struct {
    uint32_t dummy;
} TIM_HandleTypeDef;

extern TIM_HandleTypeDef hi2c1;

static inline int HAL_I2C_Mem_Write(void *hi2c, uint16_t addr, uint16_t reg,
                                    uint16_t size, uint8_t *data, uint16_t len,
                                    uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)reg;
    (void)size;
    (void)data;
    (void)len;
    (void)timeout;
    return 0;
}

static inline int HAL_I2C_Mem_Read(void *hi2c, uint16_t addr, uint16_t reg,
                                   uint16_t size, uint8_t *data, uint16_t len,
                                   uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)reg;
    (void)size;
    (void)len;
    (void)timeout;

    for (uint16_t i = 0; i < len; i++)
        data[i] = 0;

    return 0;
}

#endif /* HAL_I2C_MOCK_H */
