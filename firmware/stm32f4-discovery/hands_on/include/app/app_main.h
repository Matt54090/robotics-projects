/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_MAIN_H
#define APP_MAIN_H

#include <stdint.h>

#include "common/common_hands_on.h"

typedef struct {
    system_state_e state;
    uint32_t tick;
} app_ctx_t;

int app_main_init(app_ctx_t *ctx);
int app_main_run(app_ctx_t *ctx);

#endif /* APP_MAIN_H */
