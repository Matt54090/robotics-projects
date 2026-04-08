/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_vari_r.h"

#include "bsp/bsp_adc.h"

#define ADC_MAX_VALUE 4095
#define ADC_VREF 3.3f

static int _read_raw(uint32_t *val);

void dev_vari_r_init(void)
{
    bsp_adc_init();
}

float dev_vari_r_read_voltage(void)
{
    uint32_t raw = 0;
    if (_read_raw(&raw) < 0)
        return 0.0f;

    return (raw / (float)ADC_MAX_VALUE) * ADC_VREF;
}

static int _read_raw(uint32_t *val)
{
    return bsp_adc_read(val);
}
