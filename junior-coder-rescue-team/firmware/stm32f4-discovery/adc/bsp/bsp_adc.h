/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_ADC_H
#define BSP_ADC_H

#include <stdint.h>

void bsp_adc_init(void);
int bsp_adc_read(uint32_t *value);

#endif /* BSP_ADC_H */
