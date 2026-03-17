/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_led.h"

#ifdef UNIT_TEST
#include "board_pwm_config.h"
#include "hal_pwm_mock.h"
#else
#include "stm32f4xx_hal.h"
#include "tim.h"
#endif

void bsp_led_pwm_init(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void bsp_led_pwm_set(uint16_t duty)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);
}

uint32_t bsp_led_pwm_time_get_tick(void)
{
    return HAL_GetTick();
}
