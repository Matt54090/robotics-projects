/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "common/common_hands_on.h"

#ifdef UNIT_TEST
#include "common/hal_mock.h"
#else
#include "gpio.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#endif

void dev_delay_ms(uint32_t ms)
{
    bsp_delay_ms(ms);
}

uint32_t dev_get_tick(void)
{
    return bsp_get_tick();
}

void bsp_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

uint32_t bsp_get_tick(void)
{
    return HAL_GetTick();
}
