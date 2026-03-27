/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_adc.h"

#include "dev_adc.h"

#ifdef UNIT_TEST
#include <stdio.h>

#define dev_printf printf
#else
#include "dev_uart.h"
#endif

void app_adc_init(void)
{
    dev_adc_init();
}

void app_adc_run(void)
{
    float voltage = dev_adc_read_voltage();

    dev_printf("[ADC] voltage = %.2f V\r\n", voltage);
}
