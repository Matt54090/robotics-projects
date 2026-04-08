/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_i2c.h"

#include "common/board_config.h"
#include "common/common_hands_on.h"

#ifdef UNIT_TEST
#define I2C_MEMADD_SIZE_8BIT 0x01
#endif

int bsp_i2c_write(uint16_t dev_addr, uint8_t reg, uint8_t data)
{
    return HAL_I2C_Mem_Write(&BOARD_I2C_HANDLE, dev_addr, reg,
                             I2C_MEMADD_SIZE_8BIT, &data, 1, TIMEOUT);
}

int bsp_i2c_read(uint16_t dev_addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Mem_Read(&BOARD_I2C_HANDLE, dev_addr, reg,
                            I2C_MEMADD_SIZE_8BIT, buf, len, TIMEOUT);
}

int bsp_i2c_write_addr_only(uint16_t dev_addr, uint8_t data, uint16_t len)
{
    return HAL_I2C_Master_Transmit(&BOARD_I2C_HANDLE, dev_addr, &data, len,
                                   TIMEOUT);
}
