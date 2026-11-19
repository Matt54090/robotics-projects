/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_I2C_CONFIG_H
#define BOARD_I2C_CONFIG_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "hal_i2c_mock.h"

extern TIM_HandleTypeDef hi2c1;
#else
#include "stm32f4xx_hal.h"

#define BOARD_I2C_HANDLE hi2c1
#endif

#endif /* BOARD_I2C_CONFIG_H */
