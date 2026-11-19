/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_adc.h"

#include "bsp_adc.h"
#include "common_adc.h"

int dev_adc_init(void)
{
    return 0;
}

int dev_adc_read_raw(uint32_t *val)
{
    return bsp_adc_read(val);
}

float dev_adc_read_voltage(void)
{
    uint32_t raw = 0;

    if (dev_adc_read_raw(&raw) < 0)
        return 0.0f;

    return (raw / (float)ADC_MAX_VALUE) * ADC_VREF;
}
