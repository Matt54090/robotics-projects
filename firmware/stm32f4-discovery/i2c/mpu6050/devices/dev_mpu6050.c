/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_mpu6050.h"

#include "bsp_mpu6050.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

int dev_mpu6050_init(void)
{
    return bsp_mpu6050_write(MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 0x00);
}

int dev_mpu6050_read_id(uint8_t *id)
{
    return bsp_mpu6050_read(MPU6050_ADDR, MPU6050_REG_WHO_AM_I, id, 1);
}

int dev_mpu6050_read(mpu6050_ctx_t *ctx)
{
    uint8_t buf[16] = {
        0,
    };

    int ret = bsp_mpu6050_read(MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, buf,
                               sizeof(buf));
    if (ret < 0)
        return ret;

    ctx->data.ax = (int16_t)(buf[0] << 8 | buf[1]);
    ctx->data.ay = (int16_t)(buf[2] << 8 | buf[3]);
    ctx->data.az = (int16_t)(buf[4] << 8 | buf[5]);

    ctx->data.gx = (int16_t)(buf[8] << 8 | buf[9]);
    ctx->data.gy = (int16_t)(buf[10] << 8 | buf[11]);
    ctx->data.gz = (int16_t)(buf[12] << 8 | buf[13]);

    return 0;
}

void dev_mpu6050_print_id(uint8_t id)
{
    dev_printf("id: 0x%2x\n\r", id);
}

void dev_mpu6050_print(mpu6050_ctx_t *ctx)
{
    dev_printf("acc: %d %d %d / gyro: %d %d %d\n\r", ctx->data.ax, ctx->data.ay,
               ctx->data.az, ctx->data.gx, ctx->data.gy, ctx->data.gz);
}
