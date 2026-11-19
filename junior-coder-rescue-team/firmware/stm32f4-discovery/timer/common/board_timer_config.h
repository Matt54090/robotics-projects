/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_TIMER_CONFIG_H
#define BOARD_TIMER_CONFIG_H

#ifdef UNIT_TEST
#include "hal_timer_mock.h"

extern TIM_HandleTypeDef htim3;

#define BOARD_TIMER_HANDLE (&htim3)
#else
#include "stm32f4xx_hal.h"
#include "tim.h"

#define BOARD_TIMER_HANDLE (&htim3)
#endif

#define TRIG_GPIO_Port GPIOC
#define TRIG_Pin GPIO_PIN_9

#define ECHO_GPIO_Port GPIOC
#define ECHO_Pin GPIO_PIN_8

#endif /* BOARD_TIMER_CONFIG_H */
