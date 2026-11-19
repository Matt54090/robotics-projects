/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_led.h"

#include "bsp_led.h"
#include "common_led.h"

void app_led_init(app_led_ctx_t *app_ctx)
{
    dev_led_init(&app_ctx->led_ctx);
    app_ctx->state = APP_LED_STATE_UP;
    app_ctx->last_tick = bsp_led_pwm_time_get_tick();
}

void app_led_run(app_led_ctx_t *app_ctx)
{
    uint32_t now = bsp_led_pwm_time_get_tick();
    if (now - app_ctx->last_tick >= LED_STEP_INTERVAL_MS)
    {
        app_ctx->last_tick = now;

        if (app_ctx->state == APP_LED_STATE_UP)
        {
            dev_led_set_brightness(&app_ctx->led_ctx,
                                   app_ctx->led_ctx.brightness +
                                       LED_STEP_VALUE);

            if (app_ctx->led_ctx.brightness >= LED_BRIGHTNESS_MAX)
                app_ctx->state = APP_LED_STATE_DOWN;
        }
        else
        {
            dev_led_set_brightness(&app_ctx->led_ctx,
                                   app_ctx->led_ctx.brightness -
                                       LED_STEP_VALUE);

            if (app_ctx->led_ctx.brightness <= LED_BRIGHTNESS_MIN)
                app_ctx->state = APP_LED_STATE_UP;
        }
    }
}
