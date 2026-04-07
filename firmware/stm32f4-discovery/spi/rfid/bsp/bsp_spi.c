/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_spi.h"

#include "board_spi_config.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

#define RC522_CS_LOW()                                                         \
    HAL_GPIO_WritePin(RC522_CS_PORT, RC522_CS_PIN, GPIO_PIN_RESET)
#define RC522_CS_HIGH()                                                        \
    HAL_GPIO_WritePin(RC522_CS_PORT, RC522_CS_PIN, GPIO_PIN_SET)

void bsp_spi_init(void)
{
    RC522_CS_HIGH();
}

int bsp_spi_write(uint8_t reg, uint8_t data)
{
    uint8_t buf[2];

    buf[0] = (reg << 1) & 0x7E;
    buf[1] = data;

    RC522_CS_HIGH();
    HAL_Delay(1);
    RC522_CS_LOW();
    HAL_Delay(1);

    int ret = HAL_SPI_Transmit(&hspi1, buf, 2, 100);
    if (ret != HAL_OK)
    {
        dev_printf("SPI TX Error: %d\n", ret);
    }
    RC522_CS_HIGH();

    return ret;
}

int bsp_spi_read(uint8_t reg, uint8_t *data)
{
    uint8_t tx[2];
    uint8_t rx[2];

    tx[0] = ((reg << 1) & 0x7E) | 0x80;
    tx[1] = 0x00;

    RC522_CS_HIGH();
    HAL_Delay(1);
    RC522_CS_LOW();
    HAL_Delay(1);

    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, 1000);
    RC522_CS_HIGH();

    *data = rx[1];
    return 0;
}

void bsp_spi_delay(uint32_t ms)
{
    HAL_Delay(ms);
}
