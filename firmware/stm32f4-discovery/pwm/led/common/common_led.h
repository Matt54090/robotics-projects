/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_LED_H
#define COMMON_LED_H

typedef enum {
    LED_PWM_FREQ_HZ = 1000,
    LED_PWM_PERIOD_TICKS = 999,
    LED_PWM_PRESCALER = 83,
} led_pwm_spec_e;

typedef enum {
    LED_BRIGHTNESS_MIN = 0,
    LED_BRIGHTNESS_MAX = 999,
} led_brightness_range_e;

typedef enum {
    LED_STEP_VALUE = 10,
    LED_STEP_INTERVAL_MS = 5
} led_step_spec_e;

#endif /* COMMON_LED_H */
