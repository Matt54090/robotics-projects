/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_ADC_MOCK_H
#define HAL_ADC_MOCK_H

#include <stdint.h>

#define HAL_OK 0

typedef struct {
    int dummy;
} ADC_HandleTypeDef;

extern ADC_HandleTypeDef hadc1;

static inline int HAL_ADC_Start(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return HAL_OK;
}

static inline int HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc,
                                            uint32_t timeout)
{
    (void)hadc;
    (void)timeout;

    return HAL_OK;
}

static inline uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return 0;
}

static inline int HAL_ADC_Stop(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return HAL_OK;
}

#endif /* HAL_ADC_MOCK_H */
