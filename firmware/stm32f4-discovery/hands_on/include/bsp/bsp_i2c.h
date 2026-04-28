/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_I2C_H
#define BSP_I2C_H

#include <stdint.h>

int bsp_i2c_write(uint16_t dev_addr, uint8_t reg, uint8_t data, uint16_t len);
int bsp_i2c_read(uint16_t dev_addr, uint8_t reg, uint8_t *buf, uint16_t len);

int bsp_i2c_write_addr_only(uint16_t dev_addr, uint8_t data, uint16_t len);

#endif /* BSP_I2C_H */
