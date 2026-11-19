/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_mpu6050.h"

#ifdef UNIT_TEST
#include "board_i2c_config.h"
#include "hal_i2c_mock.h"
#else
#include "i2c.h"
#include "stm32f4xx_hal.h"
#endif

void bsp_mpu6050_init(void)
{
}

int bsp_mpu6050_write(uint16_t dev_addr, uint8_t reg, uint8_t data)
{
    return HAL_I2C_Mem_Write(&hi2c1, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, &data,
                             1, 100);
}

int bsp_mpu6050_read(uint16_t dev_addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, buf,
                            len, 100);
}
