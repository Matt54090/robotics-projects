/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_servo.h"

#include "bsp/bsp_pwm.h"

enum {
    SERVO_PULSE_OPEN = 2000,
    SERVO_PULSE_CLOSE = 1000
};

void dev_servo_init(void)
{
    bsp_pwm_init();

    dev_servo_close();
}

void dev_servo_open(void)
{
    bsp_pwm_set_pulse(SERVO_PULSE_OPEN);
}

void dev_servo_close(void)
{
    bsp_pwm_set_pulse(SERVO_PULSE_CLOSE);
}
