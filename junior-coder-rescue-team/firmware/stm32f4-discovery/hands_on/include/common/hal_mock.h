/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_MOCK_H
#define HAL_MOCK_H

#include <stdint.h>

#define HAL_OK 0

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

#define GPIOA (&gpioA_instance)
#define GPIOB (&gpioB_instance)
#define GPIOC (&gpioC_instance)

#define GPIO_PIN_4 (1U << 4)
#define GPIO_PIN_8 (1U << 8)
#define GPIO_PIN_9 (1U << 9)

#define GPIO_PIN_12 (1U << 12)
#define GPIO_PIN_13 (1U << 13)
#define GPIO_PIN_14 (1U << 14)

#define TIM_CHANNEL_2 2

typedef struct {
    uint32_t dummy;
} GPIO_TypeDef;

typedef struct {
    int dummy;
    void *pUserData;
} UART_HandleTypeDef;

typedef struct {
    int dummy;
} I2C_HandleTypeDef;

typedef struct {
    uint32_t dummy;
} SPI_HandleTypeDef;

typedef struct {
    uint32_t dummy;

    void *Instance;
    uint32_t Channel;
    uint32_t counter;
} TIM_HandleTypeDef;

typedef struct {
    int dummy;
} ADC_HandleTypeDef;

static GPIO_TypeDef gpioA_instance __attribute__((unused));
static GPIO_TypeDef gpioB_instance __attribute__((unused));
static GPIO_TypeDef gpioC_instance __attribute__((unused));

extern UART_HandleTypeDef huart2;

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern SPI_HandleTypeDef hspi1;

extern ADC_HandleTypeDef hadc1;

static inline void HAL_GPIO_WritePin(GPIO_TypeDef *port, int pin, int state)
{
    (void)port;
    (void)pin;
    (void)state;
}

static inline int HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *data,
                                       uint16_t len)
{
    (void)huart;
    (void)data;
    (void)len;

    return HAL_OK;
}

static inline int HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *data,
                                      uint16_t len)
{
    (void)huart;
    (void)data;
    (void)len;

    return HAL_OK;
}

static inline int HAL_I2C_Mem_Write(void *hi2c, uint16_t addr, uint16_t reg,
                                    uint16_t size, uint8_t *data, uint16_t len,
                                    uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)reg;
    (void)size;
    (void)data;
    (void)len;
    (void)timeout;
    return 0;
}

static inline int HAL_I2C_Mem_Read(void *hi2c, uint16_t addr, uint16_t reg,
                                   uint16_t size, uint8_t *data, uint16_t len,
                                   uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)reg;
    (void)size;
    (void)data;
    (void)len;
    (void)timeout;

    return 0;
}

static inline int HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c,
                                          uint16_t addr, uint8_t *data,
                                          uint16_t size, uint32_t timeout)
{
    (void)hi2c;
    (void)addr;
    (void)data;
    (void)size;
    (void)timeout;

    return 0;
}

static inline void HAL_TIM_PWM_Start(void *htim, uint32_t channel)
{
    (void)htim;
    (void)channel;
}

static inline void __HAL_TIM_SET_COMPARE(void *htim, uint32_t channel,
                                         uint32_t pulse)
{
    (void)htim;
    (void)channel;
    (void)pulse;
}

static inline int HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t ch)
{
    (void)htim;
    (void)ch;

    return 0;
}

static inline uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim,
                                                 uint32_t ch)
{
    (void)htim;
    (void)ch;

    return 0;
}

static inline void __HAL_TIM_SET_CAPTUREPOLARITY(TIM_HandleTypeDef *htim,
                                                 uint32_t ch, uint32_t polarity)
{
    (void)htim;
    (void)ch;
    (void)polarity;
}

static inline uint32_t __HAL_TIM_GET_COUNTER(TIM_HandleTypeDef *htim)
{
    (void)htim;

    return 0;
}

static inline uint32_t __HAL_TIM_GET_AUTORELOAD(TIM_HandleTypeDef *htim)
{
    (void)htim;

    return 0;
}

static inline int HAL_SPI_TransmitReceive(void *hspi, uint8_t *tx, uint8_t *rx,
                                          uint16_t len, uint32_t timeout)
{
    (void)hspi;
    (void)tx;
    (void)rx;
    (void)len;
    (void)timeout;

    return 0;
}

static inline int HAL_ADC_Start(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return HAL_OK;
}

static inline int HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc,
                                            uint32_t timeout)
{
    (void)hadc;
    (void)timeout;

    return HAL_OK;
}

static inline uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return 0;
}

static inline int HAL_ADC_Stop(ADC_HandleTypeDef *hadc)
{
    (void)hadc;

    return HAL_OK;
}

static inline void HAL_Delay(uint32_t ms)
{
    (void)ms;
}

static inline uint32_t HAL_GetTick(void)
{
    return 0;
}

#endif /* HAL_MOCK_H */
