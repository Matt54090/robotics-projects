/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_ADC_CONFIG_H
#define BOARD_ADC_CONFIG_H

#ifdef UNIT_TEST
#include "hal_adc_mock.h"
extern ADC_HandleTypeDef hadc1;
#else
#include "adc.h"
#include "stm32f4xx_hal.h"

#define BOARD_ADC_HANDLE (&hadc1)
#endif

#endif /* BOARD_ADC_CONFIG_H */
