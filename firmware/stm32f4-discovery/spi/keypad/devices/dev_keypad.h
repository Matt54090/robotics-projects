/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_KEYPAD_H
#define DEV_KEYPAD_H

#include <stdint.h>

typedef struct {
    int last_key;
} keypad_ctx_t;

int dev_keypad_init(keypad_ctx_t *ctx);
int dev_keypad_read_key(keypad_ctx_t *ctx);
void dev_keypad_print_key(int key);

#endif /* DEV_KEYPAD_H */
