/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "bsp_keypad.h"

#include "board_keypad_config.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

#define KEYPAD_CS_LOW()                                                        \
    HAL_GPIO_WritePin(KEYPAD_CS_PORT, KEYPAD_CS_PIN, GPIO_PIN_RESET)
#define KEYPAD_CS_HIGH()                                                       \
    HAL_GPIO_WritePin(KEYPAD_CS_PORT, KEYPAD_CS_PIN, GPIO_PIN_SET)

void bsp_spi_init(void)
{
    KEYPAD_CS_HIGH();
}

int bsp_spi_transceive(uint8_t *tx, uint8_t *rx, uint16_t len)
{
    KEYPAD_CS_HIGH();

    KEYPAD_CS_LOW();
    int ret = HAL_SPI_TransmitReceive(&hspi1, tx, rx, len, 100);
    KEYPAD_CS_HIGH();
    if (ret != HAL_OK)
    {
        dev_printf("SPI TRX Error: %d\n", ret);
        return -1;
    }

    return 0;
}

void bsp_spi_delay(uint32_t ms)
{
    HAL_Delay(ms);
}

uint32_t bsp_spi_get_tick(void)
{
    return HAL_GetTick();
}
