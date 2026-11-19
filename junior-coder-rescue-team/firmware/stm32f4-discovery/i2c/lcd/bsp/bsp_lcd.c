/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_lcd.h"

#include "common_i2c.h"

#ifdef UNIT_TEST
#include "board_i2c_config.h"
#else
#include "i2c.h"
#include "stm32f4xx_hal.h"
#endif

int bsp_lcd_write(uint8_t data)
{
    return HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &data, 1, 100);
}

void bsp_lcd_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}
