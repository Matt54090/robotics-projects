/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_pwm.h"

void app_pwm_init(app_servo_ctx_t *ctx)
{
    dev_servo_init(&ctx->servo);
    dev_servo_set_angle(&ctx->servo, SERVO_POS_CLOSED);

    ctx->state = APP_SERVO_STATE_IDLE;
    ctx->last_tick = dev_servo_time_get_tick();
}

void app_pwm_run(app_servo_ctx_t *ctx)
{
    uint32_t now = dev_servo_time_get_tick();
    if (now - ctx->last_tick >= SERVO_TOGGLE_INTERVAL_MS)
    {
        ctx->last_tick = now;
        if (ctx->state == 0)
        {
            dev_servo_set_angle(&ctx->servo, SERVO_ANGLE_OPEN);
            ctx->state = APP_SERVO_STATE_OPENED;
        }
        else
        {
            dev_servo_set_angle(&ctx->servo, SERVO_ANGLE_CLOSED);
            ctx->state = APP_SERVO_STATE_IDLE;
        }
    }
}
