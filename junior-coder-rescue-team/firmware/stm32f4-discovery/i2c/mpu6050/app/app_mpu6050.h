/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_MPU6050_H
#define APP_MPU6050_H

#include "dev_mpu6050.h"

typedef struct {
    mpu6050_ctx_t dev;
    uint8_t whoami;
} app_mpu6050_ctx_t;

void app_mpu6050_init(app_mpu6050_ctx_t *ctx);
void app_mpu6050_run(app_mpu6050_ctx_t *ctx);

#endif /* APP_MPU6050_H */
