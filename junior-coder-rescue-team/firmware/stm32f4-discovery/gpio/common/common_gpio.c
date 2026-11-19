/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "common_gpio.h"

#ifdef UNIT_TEST
#include "hal_gpio_mock.h"
#else
#include "stm32f4xx_hal.h"
#endif

void gpio_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}
