/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_keypad.h"

#include "bsp_keypad.h"
#include "common_keypad.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

#define DEBOUNCE_MS 50

static void _mcp_write(uint8_t reg, uint8_t val);
static uint8_t _mcp_read(uint8_t reg);

int dev_keypad_init(keypad_ctx_t *ctx)
{
    ctx->last_key = KEYPAD_NONE;

    bsp_spi_init();

    _mcp_write(MCP_REG_IODIRA, 0xE1);
    _mcp_write(MCP_REG_IODIRB, 0x1E);
    _mcp_write(MCP_REG_GPPUB, 0x1E);

    _mcp_write(MCP_REG_FIFO_LEVEL, 0x30);

    return 0;
}

int dev_keypad_read_key(keypad_ctx_t *ctx)
{

    static const int key_map[4][4] = {
        {1, 2, 3, 'A'}, {4, 5, 6, 'B'}, {7, 8, 9, 'C'}, {'*', 0, '#', 'D'}};
    static uint32_t s_last_time = 0;

    for (int row_idx = 0; row_idx < 4; row_idx++)
    {
        uint8_t row_mask = ~(1 << (row_idx + 1)) & 0x1E;

        _mcp_write(MCP_REG_OLATA, row_mask);
        bsp_spi_delay(1);

        uint8_t raw = (_mcp_read(MCP_REG_GPIOB) >> 1) & 0x0F;
        if (raw != 0x0F)
        {
            uint8_t active = (~raw) & 0x0F;

            for (int col_idx = 0; col_idx < 4; col_idx++)
            {
                if (active & (1 << col_idx))
                {
                    int key = key_map[row_idx][col_idx];
                    uint32_t now = bsp_spi_get_tick();

                    if (key != ctx->last_key &&
                        (now - s_last_time) > DEBOUNCE_MS)
                    {
                        ctx->last_key = key;
                        s_last_time = now;
                        return key;
                    }
                }
            }
        }
    }

    return -1;
}
void dev_keypad_print_key(int key)
{
    if (key < 0)
        return;

    dev_printf("KEY: %d\n\r", key);
}

static void _mcp_write(uint8_t reg, uint8_t val)
{
    uint8_t tx[3] = {MCP_OPCODE_WRITE, reg, val};
    uint8_t rx[3];

    bsp_spi_transceive(tx, rx, 3);
}

static uint8_t _mcp_read(uint8_t reg)
{
    uint8_t tx[3] = {MCP_OPCODE_READ, reg, 0xFF};
    uint8_t rx[3] = {
        0,
    };

    bsp_spi_transceive(tx, rx, 3);

    return rx[2];
}
