/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_lcd.h"

#include <stdarg.h>
#include <stdio.h>

#include "bsp/bsp_i2c.h"
#include "common/common_hands_on.h"

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

static void _send_half_byte(uint8_t half, uint8_t rs);
static void _send_command(uint8_t cmd);
static void _send_data(uint8_t data);
static void _lcd_print(const char *str);

void dev_lcd_init(void)
{
    bsp_delay_ms(50);

    _send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    bsp_delay_ms(5);

    _send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    bsp_delay_ms(1);

    _send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    _send_half_byte(LCD_INIT_STEP_SET_4BIT, 0);

    _send_command(LCD_CMD_FUNCTION_SET_4BIT_2LINE);
    _send_command(LCD_CMD_DISPLAY_ON);
    _send_command(LCD_CMD_ENTRY_MODE);
    _send_command(LCD_CMD_CLEAR);

    bsp_delay_ms(2);
}

void dev_lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t base = (row == 0) ? LCD_ROW0_BASE : LCD_ROW1_BASE;
    _send_command(LCD_CMD_SET_DDRAM | (base + col));
}

void dev_lcd_printf(const char *fmt, ...)
{
    char buf[32];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    _lcd_print(buf);
}

void dev_lcd_backlight_set(uint8_t on)
{
    lcd_backlight_e backlight = on ? LCD_BACKLIGHT_ON : LCD_BACKLIGHT_OFF;
    bsp_i2c_write_addr_only(LCD_I2C_ADDR, backlight, sizeof(uint8_t));
}

static void _send_half_byte(uint8_t half, uint8_t rs)
{
    uint8_t data = (half << 4) | LCD_BACKLIGHT_ON;

    if (rs)
        data |= LCD_RS_BIT;

    bsp_i2c_write_addr_only(LCD_I2C_ADDR, data | LCD_ENABLE_BIT,
                            sizeof(uint8_t));
    bsp_delay_ms(0);
    bsp_i2c_write_addr_only(LCD_I2C_ADDR, data, sizeof(uint8_t));
}

static void _send_command(uint8_t cmd)
{
    _send_half_byte(cmd >> 4, 0);
    _send_half_byte(cmd & 0x0F, 0);
}

static void _send_data(uint8_t data)
{
    _send_half_byte(data >> 4, 1);
    _send_half_byte(data & 0x0F, 1);
}

static void _lcd_print(const char *str)
{
    while (*str)
    {
        _send_data((uint8_t)(*str));
        str++;
    }
}
