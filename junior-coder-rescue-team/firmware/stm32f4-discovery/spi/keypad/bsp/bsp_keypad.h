/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_KEYPAD_H
#define BSP_KEYPAD_H

#include <stdint.h>

void bsp_spi_init(void);
int bsp_spi_transceive(uint8_t *tx, uint8_t *rx, uint16_t len);

void bsp_spi_delay(uint32_t ms);
uint32_t bsp_spi_get_tick(void);

#endif /* BSP_KEYPAD_H */
