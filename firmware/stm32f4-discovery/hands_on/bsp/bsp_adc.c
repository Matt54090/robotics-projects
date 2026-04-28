/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_adc.h"

#include "common/board_config.h"
#include "common/common_hands_on.h"

enum {
    ADC_TIMEOUT_MS = 10,
};

int bsp_adc_init(void)
{
    HAL_ADC_Start(&BOARD_ADC_HANDLE);

    return 0;
}

int bsp_adc_read(uint32_t *value)
{
    if (HAL_ADC_Start(&BOARD_ADC_HANDLE) != HAL_OK)
        return RETURN_ERROR;

    if (HAL_ADC_PollForConversion(&BOARD_ADC_HANDLE, ADC_TIMEOUT_MS) != HAL_OK)
        return RETURN_ERROR;

    *value = HAL_ADC_GetValue(&BOARD_ADC_HANDLE);

    HAL_ADC_Stop(&BOARD_ADC_HANDLE);

    return 0;
}
