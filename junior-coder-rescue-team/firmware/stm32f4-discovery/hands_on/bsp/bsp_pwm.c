/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_pwm.h"

#include "common/board_config.h"

void bsp_pwm_init(void)
{
    HAL_TIM_PWM_Start(&BOARD_PWM_HANDLE, BOARD_PWM_TIM_CHANNEL);
}

void bsp_pwm_set_pulse(uint16_t pulse)
{
    __HAL_TIM_SET_COMPARE(&BOARD_PWM_HANDLE, BOARD_PWM_TIM_CHANNEL, pulse);
}
