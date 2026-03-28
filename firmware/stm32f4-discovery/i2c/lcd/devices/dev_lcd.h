/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_LCD_H
#define DEV_LCD_H

#include <stdint.h>

void dev_lcd_init(void);
void dev_lcd_set_cursor(uint8_t row, uint8_t col);
void dev_lcd_printf(const char *fmt, ...);
void dev_lcd_backlight_set(uint8_t on);

#endif /* DEV_LCD_H */
