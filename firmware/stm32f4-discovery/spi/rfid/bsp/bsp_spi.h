/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_SPI_H
#define BSP_SPI_H

#include <stdint.h>

void bsp_spi_init(void);
int bsp_spi_write(uint8_t reg, uint8_t data);
int bsp_spi_read(uint8_t reg, uint8_t *data);
int bsp_spi_transceive(uint8_t *tx, uint8_t *rx, uint16_t len);

void bsp_spi_delay(uint32_t ms);

#endif /* BSP_SPI_H */
