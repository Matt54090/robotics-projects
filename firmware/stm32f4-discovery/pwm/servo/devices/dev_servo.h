/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_SERVO_H
#define DEV_SERVO_H

#include <stdint.h>

#include "common_pwm.h"

typedef enum {
    SERVO_POS_CLOSED,
    SERVO_POS_OPEN,
} servo_pos_e;

typedef struct {
    uint16_t current_pulse;
} servo_ctx_t;

void dev_servo_init(servo_ctx_t *ctx);
void dev_servo_set_angle(servo_ctx_t *ctx, uint8_t angle);
void dev_servo_set_position(servo_ctx_t *ctx, servo_pos_e pos);
uint32_t dev_servo_time_get_tick(void);

#endif /* DEV_SERVO_H */
