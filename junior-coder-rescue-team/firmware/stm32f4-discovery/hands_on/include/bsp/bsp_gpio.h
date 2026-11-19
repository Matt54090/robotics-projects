/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "common/common_hands_on.h"

#ifdef UNIT_TEST
#include "common/hal_mock.h"
#else
#include "stm32f4xx_hal.h"
#endif

int bsp_gpio_write(led_e led, int state);

#endif /* BSP_GPIO_H */
