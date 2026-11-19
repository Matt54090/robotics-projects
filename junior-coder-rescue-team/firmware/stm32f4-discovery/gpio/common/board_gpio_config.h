/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_GPIO_CONFIG_H
#define BOARD_GPIO_CONFIG_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "hal_gpio_mock.h"

extern GPIO_TypeDef mock_gpio_b;

#define GPIO_G_LED_GPIO_Port &mock_gpio_b
#define GPIO_G_LED_Pin 12
#else
#include "stm32f4xx_hal.h"

#define GPIO_G_LED_GPIO_Port GPIOB
#define GPIO_G_LED_Pin GPIO_PIN_12
#endif

#endif
