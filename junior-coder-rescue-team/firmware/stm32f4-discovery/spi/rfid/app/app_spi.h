/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef APP_RC522_H
#define APP_RC522_H

#include "dev_rfid.h"

typedef struct {
    rc522_ctx_t dev;
    uint8_t version;
} app_rc522_ctx_t;

void app_spi_init(app_rc522_ctx_t *ctx);
void app_spi_run(app_rc522_ctx_t *ctx);

#endif
