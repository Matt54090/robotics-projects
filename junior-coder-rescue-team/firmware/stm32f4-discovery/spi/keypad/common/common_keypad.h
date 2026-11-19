/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_KEYPAD_H
#define COMMON_KEYPAD_H

#include <stdint.h>

typedef enum {
    MCP_OPCODE_WRITE = 0x40,
    MCP_OPCODE_READ = 0x41,
} mcp_opcode_e;

typedef enum {
    MCP_REG_IODIRA = 0x00,
    MCP_REG_IODIRB = 0x01,
    MCP_REG_FIFO_LEVEL = 0x0A,
    MCP_REG_GPPUB = 0x0D,
    MCP_REG_GPIOA = 0x12,
    MCP_REG_GPIOB = 0x13,
    MCP_REG_OLATA = 0x14
} mcp_reg_e;

typedef enum {
    KEYPAD_NONE = -1,
} keypad_key_e;

#endif /* COMMON_KEYPAD_H */
