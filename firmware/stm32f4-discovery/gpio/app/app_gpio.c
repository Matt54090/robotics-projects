/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_gpio.h"

#include "common_gpio.h"
#include "dev_gpio.h"

void app_gpio_init(void)
{
}

void app_gpio_run(void)
{
    dev_led_on();
    gpio_delay_ms(1000);

    dev_led_off();
    gpio_delay_ms(1000);
}
