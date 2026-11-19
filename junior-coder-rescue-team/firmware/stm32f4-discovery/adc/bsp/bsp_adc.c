/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_adc.h"

#ifdef UNIT_TEST
#include "board_adc_config.h"
#include "hal_adc_mock.h"
#else
#include "adc.h"
#include "stm32f4xx_hal.h"
#endif

void bsp_adc_init(void)
{
}

int bsp_adc_read(uint32_t *value)
{
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
        return -1;

    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
        return -1;

    *value = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    return 0;
}
