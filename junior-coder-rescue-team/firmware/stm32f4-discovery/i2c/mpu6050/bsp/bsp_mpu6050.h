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

void bsp_mpu6050_init(void);
int bsp_mpu6050_write(uint16_t dev_addr, uint8_t reg, uint8_t data);
int bsp_mpu6050_read(uint16_t dev_addr, uint8_t reg, uint8_t *buf,
                     uint16_t len);

#endif /* BSP_I2C_H */
