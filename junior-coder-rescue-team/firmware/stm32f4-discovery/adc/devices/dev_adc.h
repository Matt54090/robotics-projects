/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_ADC_H
#define DEV_ADC_H

#include <stdint.h>

int dev_adc_init(void);
int dev_adc_read_raw(uint32_t *val);
float dev_adc_read_voltage(void);

#endif /* DEV_ADC_H */
