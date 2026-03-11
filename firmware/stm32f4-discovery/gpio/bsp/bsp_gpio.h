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

#ifdef UNIT_TEST
#include "hal_gpio_mock.h"
#else
#include "stm32f4xx_hal.h"
#endif

void bsp_gpio_write(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state);

#endif /* BSP_GPIO_H */
