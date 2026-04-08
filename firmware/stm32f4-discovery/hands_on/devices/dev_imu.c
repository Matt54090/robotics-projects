/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_imu.h"

#include <math.h>

#include "bsp/bsp_i2c.h"
#include "devices/dev_log.h"

#define ACCEL_SCALE 16384.0f

typedef enum {
    MPU6050_ADDR = 0x68 << 1,

    MPU6050_REG_PWR_MGMT_1 = 0x6B,
    MPU6050_REG_WHO_AM_I = 0x75,
    MPU6050_REG_ACCEL_XOUT_H = 0x3B,

    MPU6050_EXPECTED_ID = 0x68
} mpu6050_def_e;

int dev_imu_init(void)
{
    return bsp_i2c_write(MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 0x00);
}

int dev_imu_read_id(uint8_t *id)
{
    return bsp_i2c_read(MPU6050_ADDR, MPU6050_REG_WHO_AM_I, id, 1);
}

float dev_imu_get_accel(void)
{
    uint8_t buf[8] = {
        0,
    };

    int ret =
        bsp_i2c_read(MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, buf, sizeof(buf));
    if (ret < 0)
        return -1.0f;

    int16_t ax = (int16_t)(buf[0] << 8 | buf[1]);
    int16_t ay = (int16_t)(buf[2] << 8 | buf[3]);
    int16_t az = (int16_t)(buf[4] << 8 | buf[5]);

    float fax = ax / ACCEL_SCALE;
    float fay = ay / ACCEL_SCALE;
    float faz = az / ACCEL_SCALE;

    return sqrtf(fax * fax + fay * fay + faz * faz);
}
