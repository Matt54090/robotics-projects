/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_SPI_CONFIG_H
#define BOARD_SPI_CONFIG_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "hal_spi_mock.h"
extern SPI_HandleTypeDef hspi1;
#else
#include "gpio.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#define BOARD_SPI_HANDLE hspi1
#endif

#define RC522_CS_PORT GPIOA
#define RC522_CS_PIN GPIO_PIN_4

#endif /* BOARD_SPI_CONFIG_H */
