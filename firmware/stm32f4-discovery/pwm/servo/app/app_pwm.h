/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_PWM_H
#define APP_PWM_H

#include "dev_servo.h"

typedef enum {
    APP_SERVO_STATE_IDLE,
    APP_SERVO_STATE_OPENED,
} app_servo_state_e;

typedef enum {
    SERVO_TOGGLE_INTERVAL_MS = 3000
} app_servo_timing_e;

typedef struct {
    servo_ctx_t servo;
    app_servo_state_e state;
    uint32_t last_tick;
} app_servo_ctx_t;

void app_pwm_init(app_servo_ctx_t *ctx);
void app_pwm_run(app_servo_ctx_t *ctx);

#endif /* APP_PWM_H */
