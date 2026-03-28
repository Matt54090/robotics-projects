/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_lcd.h"

#include "dev_lcd.h"

enum {
    APP_LCD_BACKLIGHT_OFF,
    APP_LCD_BACKLIGHT_ON
};

void app_lcd_init(void)
{
    dev_lcd_init();
    dev_lcd_backlight_set(APP_LCD_BACKLIGHT_ON);
}

void app_lcd_run(void)
{
    dev_lcd_set_cursor(0, 0);
    dev_lcd_printf("Hello, World!");

    dev_lcd_set_cursor(1, 0);
    dev_lcd_printf("Hello, JCRT!");
}
