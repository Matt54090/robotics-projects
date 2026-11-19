/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_I2C_H
#define COMMON_I2C_H

#include <stdint.h>

typedef enum {
    MPU6050_ADDR = 0x68 << 1,

    MPU6050_REG_PWR_MGMT_1 = 0x6B,
    MPU6050_REG_WHO_AM_I = 0x75,
    MPU6050_REG_ACCEL_XOUT_H = 0x3B,

    MPU6050_EXPECTED_ID = 0x68
} mpu6050_def_e;

typedef struct {
    int16_t ax;
    int16_t ay;
    int16_t az;

    int16_t gx;
    int16_t gy;
    int16_t gz;
} mpu6050_data_t;

#endif /* COMMON_I2C_H */
