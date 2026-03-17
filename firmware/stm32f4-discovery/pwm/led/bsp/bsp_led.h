/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_LED_H
#define BSP_LED_H

#include <stdint.h>

#include "bsp_led.h"

void bsp_led_pwm_init(void);
void bsp_led_pwm_set(uint16_t duty);
uint32_t bsp_led_pwm_time_get_tick(void);

#endif /* BSP_LED_H */
