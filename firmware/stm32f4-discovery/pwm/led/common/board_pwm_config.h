/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_PWM_CONFIG_H
#define BOARD_PWM_CONFIG_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "hal_pwm_mock.h"

extern TIM_HandleTypeDef htim2;
#else
#include "stm32f4xx_hal.h"

#define BOARD_PWM_HANDLE htim2
#define BOARD_PWM_TIM_CHANNEL TIM_CHANNEL_2
#endif

#endif
