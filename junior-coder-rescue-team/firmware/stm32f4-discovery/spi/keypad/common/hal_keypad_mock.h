/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_KEYPAD_MOCK_H
#define HAL_KEYPAD_MOCK_H

#include <stdint.h>

#define HAL_OK 0

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

#define GPIOA (&gpioA_instance)
#define GPIO_PIN_4 (1U << 4)

typedef struct {
    uint32_t dummy;
} GPIO_TypeDef;

typedef struct {
    uint32_t dummy;
} SPI_HandleTypeDef;

static GPIO_TypeDef gpioA_instance;
extern SPI_HandleTypeDef hspi1;

static inline void HAL_GPIO_WritePin(GPIO_TypeDef *port, int pin, int state)
{
    (void)port;
    (void)pin;
    (void)state;
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

static inline void HAL_Delay(uint32_t ms)
{
    (void)ms;
}

static inline uint32_t HAL_GetTick(void)
{
    return 0;
}

#endif /* HAL_KEYPAD_MOCK_H */
