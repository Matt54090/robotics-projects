/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_gpio.h"

#include "board_gpio_config.h"
#include "bsp_gpio.h"

void dev_led_on(void)
{
    bsp_gpio_write(GPIO_G_LED_GPIO_Port, GPIO_G_LED_Pin, GPIO_PIN_SET);
}

void dev_led_off(void)
{
    bsp_gpio_write(GPIO_G_LED_GPIO_Port, GPIO_G_LED_Pin, GPIO_PIN_RESET);
}
