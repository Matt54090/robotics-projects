/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_PWM_H
#define BSP_PWM_H

#include <stdint.h>

void bsp_pwm_init(void);
void bsp_pwm_set_pulse(uint16_t pulse);

#endif /* BSP_PWM_H */
