/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_LED_H
#define APP_LED_H

#include "dev_led.h"

typedef enum {
    APP_LED_STATE_UP = 0,
    APP_LED_STATE_DOWN,
} app_led_state_e;

typedef struct {
    led_ctx_t led_ctx;
    app_led_state_e state;
    uint32_t last_tick;
} app_led_ctx_t;

void app_led_init(app_led_ctx_t *app_ctx);
void app_led_run(app_led_ctx_t *app_ctx);

#endif /* APP_LED_H */
