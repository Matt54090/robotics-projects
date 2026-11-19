/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_MPU6050_H
#define DEV_MPU6050_H

#include "common_i2c.h"

typedef struct {
    mpu6050_data_t data;
} mpu6050_ctx_t;

int dev_mpu6050_init(void);
int dev_mpu6050_read_id(uint8_t *id);
int dev_mpu6050_read(mpu6050_ctx_t *ctx);

void dev_mpu6050_print_id(uint8_t id);
void dev_mpu6050_print(mpu6050_ctx_t *ctx);

#endif
