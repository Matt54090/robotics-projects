/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_lcd.h"

#include <stdarg.h>
#include <stdio.h>

#include "bsp_lcd.h"
#include "common_i2c.h"

static void _lcd_send_half_byte(uint8_t half, uint8_t rs);
static void _lcd_send_command(uint8_t cmd);
static void _lcd_send_data(uint8_t data);
static void _lcd_print(const char *str);

void dev_lcd_init(void)
{
    bsp_lcd_delay_ms(50);

    _lcd_send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    bsp_lcd_delay_ms(5);

    _lcd_send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    bsp_lcd_delay_ms(1);

    _lcd_send_half_byte(LCD_INIT_STEP_FORCE_8BIT, 0);
    _lcd_send_half_byte(LCD_INIT_STEP_SET_4BIT, 0);

    _lcd_send_command(LCD_CMD_FUNCTION_SET_4BIT_2LINE);
    _lcd_send_command(LCD_CMD_DISPLAY_ON);
    _lcd_send_command(LCD_CMD_ENTRY_MODE);
    _lcd_send_command(LCD_CMD_CLEAR);

    bsp_lcd_delay_ms(2);
}

void dev_lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t base = (row == 0) ? LCD_ROW0_BASE : LCD_ROW1_BASE;
    _lcd_send_command(LCD_CMD_SET_DDRAM | (base + col));
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
    bsp_lcd_write(backlight);
}

static void _lcd_send_half_byte(uint8_t half, uint8_t rs)
{
    uint8_t data = (half << 4) | LCD_BACKLIGHT_ON;

    if (rs)
        data |= LCD_RS_BIT;

    bsp_lcd_write(data | LCD_ENABLE_BIT);
    bsp_lcd_delay_ms(0);
    bsp_lcd_write(data);
}

static void _lcd_send_command(uint8_t cmd)
{
    _lcd_send_half_byte(cmd >> 4, 0);
    _lcd_send_half_byte(cmd & 0x0F, 0);
}

static void _lcd_send_data(uint8_t data)
{
    _lcd_send_half_byte(data >> 4, 1);
    _lcd_send_half_byte(data & 0x0F, 1);
}

static void _lcd_print(const char *str)
{
    while (*str)
    {
        _lcd_send_data((uint8_t)(*str));
        str++;
    }
}
