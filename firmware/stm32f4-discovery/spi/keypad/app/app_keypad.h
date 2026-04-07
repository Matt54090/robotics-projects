/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_KEYPAD_H
#define APP_KEYPAD_H

#include "dev_keypad.h"

typedef struct {
    keypad_ctx_t dev;
} app_keypad_ctx_t;

void app_keypad_init(app_keypad_ctx_t *ctx);
void app_keypad_run(app_keypad_ctx_t *ctx);

#endif /* APP_KEYPAD_H */
