/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_mpu6050.h"

#include <stdio.h>

void app_mpu6050_init(app_mpu6050_ctx_t *ctx)
{
    dev_mpu6050_init();
    dev_mpu6050_read_id(&ctx->whoami);
    dev_mpu6050_print_id(ctx->whoami);
}

void app_mpu6050_run(app_mpu6050_ctx_t *ctx)
{
    dev_mpu6050_read(&ctx->dev);
    dev_mpu6050_print(&ctx->dev);
}
