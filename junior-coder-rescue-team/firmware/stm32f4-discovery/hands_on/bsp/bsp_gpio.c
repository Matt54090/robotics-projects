/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp/bsp_gpio.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} gpio_map_t;

int bsp_gpio_write(led_e led, int state)
{
    if (led >= LED_GREEN + 1)
        return RETURN_ERROR;

    const gpio_map_t led_map[] = {[LED_RED] = {GPIOB, GPIO_PIN_14},
                                  [LED_YELLOW] = {GPIOB, GPIO_PIN_13},
                                  [LED_GREEN] = {GPIOB, GPIO_PIN_12}};

    HAL_GPIO_WritePin(led_map[led].port, led_map[led].pin,
                      state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return 0;
}
