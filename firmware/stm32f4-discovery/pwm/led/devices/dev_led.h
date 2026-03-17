/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_LED_H
#define DEV_LED_H

#include <stdint.h>

typedef struct {
    uint16_t brightness;
} led_ctx_t;

void dev_led_init(led_ctx_t *ctx);
void dev_led_set_brightness(led_ctx_t *ctx, uint16_t brightness);

#endif /* DEV_LED_H */
