/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_led.h"

#include "bsp_led.h"
#include "common_led.h"

void dev_led_init(led_ctx_t *ctx)
{
    bsp_led_pwm_init();
    ctx->brightness = LED_BRIGHTNESS_MIN;
    bsp_led_pwm_set(ctx->brightness);
}

void dev_led_set_brightness(led_ctx_t *ctx, uint16_t brightness)
{
    if (brightness > LED_BRIGHTNESS_MAX)
        brightness = LED_BRIGHTNESS_MAX;

    ctx->brightness = brightness;
    bsp_led_pwm_set(ctx->brightness);
}
