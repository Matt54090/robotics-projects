/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_spi.h"

#include <string.h>

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

void app_spi_init(app_rc522_ctx_t *ctx)
{
    memset(ctx, 0x0, sizeof(app_rc522_ctx_t));

    dev_spi_init(&ctx->dev);

    dev_spi_read_version(&ctx->version);
    dev_spi_print_version(ctx->version);
}

void app_spi_run(app_rc522_ctx_t *ctx)
{
    dev_spi_read_uid(&ctx->dev);
    dev_spi_print_uid(&ctx->dev);
}
