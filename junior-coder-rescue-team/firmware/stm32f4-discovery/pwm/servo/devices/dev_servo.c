/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_servo.h"

#include "bsp_pwm.h"

void dev_servo_init(servo_ctx_t *ctx)
{
    bsp_pwm_init();
    ctx->current_pulse = SERVO_PULSE_MID_US;
}

void dev_servo_set_angle(servo_ctx_t *ctx, uint8_t angle)
{
    if (angle > SERVO_ANGLE_MAX)
        angle = SERVO_ANGLE_MAX;

    uint16_t pulse =
        SERVO_PULSE_MIN_US +
        ((SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) * angle) / SERVO_ANGLE_MAX;

    ctx->current_pulse = pulse;
    bsp_pwm_set_pulse(pulse);
}

void dev_servo_set_position(servo_ctx_t *ctx, servo_pos_e pos)
{
    switch (pos)
    {
    case SERVO_POS_OPEN:
        dev_servo_set_angle(ctx, SERVO_ANGLE_CLOSED);
        break;
    case SERVO_POS_CLOSED:
        dev_servo_set_angle(ctx, SERVO_ANGLE_OPEN);
        break;
    }
}

uint32_t dev_servo_time_get_tick(void)
{
    return bsp_pwm_time_get_tick();
}
