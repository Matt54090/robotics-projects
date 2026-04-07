/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_RC522_H
#define DEV_RC522_H

#include "common_spi.h"

typedef struct {
    rc522_uid_t uid;
} rc522_ctx_t;

int dev_spi_init(rc522_ctx_t *ctx);
int dev_spi_read_version(uint8_t *ver);
int dev_spi_read_uid(rc522_ctx_t *ctx);

void dev_spi_print_version(uint8_t ver);
void dev_spi_print_uid(rc522_ctx_t *ctx);

#endif
