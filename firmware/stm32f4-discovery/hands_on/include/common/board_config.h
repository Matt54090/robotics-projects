/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "common/hal_mock.h"

extern UART_HandleTypeDef huart2;

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern SPI_HandleTypeDef hspi1;

extern ADC_HandleTypeDef hadc1;
#else
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"
#endif

#define BOARD_UART_HANDLE huart2

#define BOARD_I2C_HANDLE hi2c1

#define BOARD_PWM_HANDLE htim4
#define BOARD_PWM_TIM_CHANNEL TIM_CHANNEL_2

#define BOARD_TIMER_HANDLE htim3

#define BOARD_SPI_HANDLE hspi1

#define BOARD_ADC_HANDLE hadc1

#define TRIG_GPIO_Port GPIOC
#define TRIG_Pin GPIO_PIN_9

#define ECHO_GPIO_Port GPIOC
#define ECHO_Pin GPIO_PIN_8

#define SPI_CS_PORT GPIOA
#define SPI_CS_PIN GPIO_PIN_4

#endif /* BOARD_CONFIG_H */
