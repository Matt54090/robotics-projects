/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_LCD_H
#define BSP_LCD_H

#include <stdint.h>

int bsp_lcd_write(uint8_t data);
void bsp_lcd_delay_ms(uint32_t ms);

#endif /* BSP_LCD_H */
