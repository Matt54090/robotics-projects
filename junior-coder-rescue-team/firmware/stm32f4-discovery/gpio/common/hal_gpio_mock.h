/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef HAL_GPIO_MOCK_H
#define HAL_GPIO_MOCK_H

#include <stdint.h>

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState;

typedef struct {
    uint32_t dummy;
} GPIO_TypeDef;

GPIO_TypeDef mock_gpio_b;

#define HAL_OK 0
#define HAL_ERROR 1

static inline int HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin,
                                    GPIO_PinState state)
{
    (void)port;
    (void)pin;
    (void)state;

    return HAL_OK;
}

static inline void HAL_Delay(uint32_t ms)
{
    (void)ms;
}

#endif /* HAL_GPIO_MOCK_H */
