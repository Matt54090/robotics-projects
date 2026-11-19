/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_led.h"

#include "bsp/bsp_gpio.h"

enum {
    LED_BLINK_INTERVAL_MS = 500
};

void dev_led_init(void)
{
    dev_led_set(LED_GREEN, LED_OFF);
    dev_led_set(LED_YELLOW, LED_OFF);
    dev_led_set(LED_RED, LED_OFF);
}

void dev_led_set(led_e led, int on)
{
    bsp_gpio_write(led, on);
}

void dev_led_blink(led_e led)
{
    static uint32_t last = 0;
    static int toggle = 0;

    if (bsp_get_tick() - last > LED_BLINK_INTERVAL_MS)
    {
        toggle = !toggle;
        dev_led_set(led, toggle);
        last = bsp_get_tick();
    }
}
