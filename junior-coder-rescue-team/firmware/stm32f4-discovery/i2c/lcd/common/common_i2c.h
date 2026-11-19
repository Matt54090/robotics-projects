/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_I2C_H
#define COMMON_I2C_H

#include <stdint.h>

typedef enum {
    LCD_I2C_ADDR = 0x27 << 1
} lcd_addr_e;

typedef enum {
    LCD_CMD_FUNCTION_SET_4BIT_2LINE = 0x28,
    LCD_CMD_DISPLAY_ON = 0x0C,
    LCD_CMD_ENTRY_MODE = 0x06,
    LCD_CMD_CLEAR = 0x01,
    LCD_CMD_SET_DDRAM = 0x80
} lcd_command_e;

typedef enum {
    LCD_INIT_STEP_FORCE_8BIT = 0x03,
    LCD_INIT_STEP_SET_4BIT = 0x02
} lcd_init_step_e;

typedef enum {
    LCD_BACKLIGHT_ON = 0x08,
    LCD_BACKLIGHT_OFF = 0x00
} lcd_backlight_e;

typedef enum {
    LCD_ENABLE_BIT = 0x04,
    LCD_RS_BIT = 0x01
} lcd_control_bit_e;

typedef enum {
    LCD_ROW0_BASE = 0x00,
    LCD_ROW1_BASE = 0x40
} lcd_row_base_e;

#endif /* COMMON_I2C_H */
