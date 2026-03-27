/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_ADC_H
#define COMMON_ADC_H

#include <stdint.h>

typedef enum {
    ADC_CH_0 = 0,
    ADC_CH_1,
    ADC_CH_2,
    ADC_CH_MAX
} adc_channel_e;

#define ADC_MAX_VALUE 4095
#define ADC_VREF 3.3f

#endif /* COMMON_ADC_H */
