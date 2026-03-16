/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_PWM_H
#define COMMON_PWM_H

#include <stdint.h>

typedef enum {
    STATUS_ERROR = -1,
    STATUS_SUCCESS,
    STATUS_BUSY
} status_e;

typedef enum {
    SERVO_PULSE_MIN_US = 500,
    SERVO_PULSE_MAX_US = 2500,
    SERVO_PULSE_MID_US = 1500
} servo_pulse_e;

typedef enum {
    SERVO_ANGLE_MIN = 0,
    SERVO_ANGLE_MAX = 180,
    SERVO_ANGLE_OPEN = 90,
    SERVO_ANGLE_CLOSED = 0
} servo_angle_e;

typedef enum {
    SERVO_PWM_PERIOD_US = 20000,
} servo_pwm_spec_e;

#endif /* COMMON_PWM_H */
