/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_pwm.h"

#ifdef UNIT_TEST
#include "board_pwm_config.h"
#include "hal_pwm_mock.h"
#else
#include "stm32f4xx_hal.h"
#include "tim.h"
#endif

void bsp_pwm_init(void)
{
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}

void bsp_pwm_set_pulse(uint16_t pulse)
{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pulse);
}

uint32_t bsp_pwm_time_get_tick(void)
{
    return HAL_GetTick();
}
