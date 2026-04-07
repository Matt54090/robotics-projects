/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_keypad.h"

#include <string.h>

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

void app_keypad_init(app_keypad_ctx_t *ctx)
{
    memset(ctx, 0x0, sizeof(app_keypad_ctx_t));

    dev_keypad_init(&ctx->dev);
}

void app_keypad_run(app_keypad_ctx_t *ctx)
{
    int key = dev_keypad_read_key(&ctx->dev);
    dev_keypad_print_key(key);
}
