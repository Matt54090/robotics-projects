/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_spi.h"

#include "bsp_spi.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

#include <string.h>

static rc522_status_t _rc522_request(uint8_t *tag_type);
static rc522_status_t _rc522_anticoll(uint8_t *uid);

int dev_spi_init(rc522_ctx_t *ctx)
{
    memset(ctx, 0x0, sizeof(rc522_ctx_t));

    bsp_spi_init();

    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_SOFT_RESET);
    bsp_spi_delay(50);

    uint8_t val;
    do
    {
        bsp_spi_read(RC522_REG_COMMAND, &val);
    } while (val & (1 << 4));
    bsp_spi_delay(10);

    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_IDLE);

    bsp_spi_write(RC522_REG_TMODE, RC522_TIMER_MODE);
    bsp_spi_write(RC522_REG_TPRESCALER, RC522_TIMER_PRESCALER);

    bsp_spi_write(RC522_REG_TRELOAD_L, RC522_TIMER_RELOAD_L);
    bsp_spi_write(RC522_REG_TRELOAD_H, RC522_TIMER_RELOAD_H);

    bsp_spi_write(RC522_REG_TX_ASK, RC522_TXASK_ENABLE);

    bsp_spi_write(RC522_REG_MODE, RC522_MODE_DEFAULT);

    bsp_spi_read(RC522_REG_TX_CONTROL, &val);
    bsp_spi_write(RC522_REG_TX_CONTROL, val | 0x03);

    bsp_spi_delay(10);

    return 0;
}

int dev_spi_read_version(uint8_t *ver)
{
    return bsp_spi_read(RC522_REG_VERSION, ver);
}

int dev_spi_read_uid(rc522_ctx_t *ctx)
{
    uint8_t tag[2] = {
        0,
    };
    uint8_t uid[5] = {
        0,
    };

    ctx->uid.valid = 0;

    rc522_status_t ret;

    ret = _rc522_request(tag);
    if (ret != RC522_OK)
        return ret;

    if ((tag[0] == 0x00 && tag[1] == 0x00) ||
        (tag[0] == 0xFF && tag[1] == 0xFF))
        return RC522_ERR_INVALID_ATQA;

    ret = _rc522_anticoll(uid);
    if (ret != RC522_OK)
        return ret;

    if ((uid[0] == 0x00 && uid[1] == 0x00 && uid[2] == 0x00 && uid[3] == 0x00))
        return RC522_ERR_INVALID_UID;

    memcpy(ctx->uid.uid, uid, 4);
    memcpy(ctx->uid.atqa, tag, 2);

    ctx->uid.uid_len = 4;
    ctx->uid.valid = 1;

    return RC522_OK;
}

void dev_spi_print_version(uint8_t ver)
{
    dev_printf("RC522 version: 0x%02X\n\r", ver);
}

void dev_spi_print_uid(rc522_ctx_t *ctx)
{
    if (ctx->uid.valid == 0)
        return;

    dev_printf("ATQA: %02X %02X\n\r", ctx->uid.atqa[0], ctx->uid.atqa[1]);

    dev_printf("UID: ");
    for (int i = 0; i < ctx->uid.uid_len; i++)
        dev_printf("%02X ", ctx->uid.uid[i]);

    dev_printf("\n\r");
}

static rc522_status_t _rc522_request(uint8_t *tag_type)
{
    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_IDLE);
    bsp_spi_write(RC522_REG_FIFO_LEVEL, 0x80);

    bsp_spi_write(RC522_REG_FIFO_DATA, PICC_CMD_REQA);
    bsp_spi_write(RC522_REG_BIT_FRAMING, RC522_BIT_FRAMING_REQA);

    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_TRANSCEIVE);
    bsp_spi_write(RC522_REG_BIT_FRAMING, RC522_BIT_FRAMING_REQA);

    bsp_spi_delay(5);

    int timeout = 100;
    uint8_t irq;

    while (timeout--)
    {
        bsp_spi_read(RC522_REG_COMM_IRQ, &irq);
        if (irq & 0x30)
            break;

        bsp_spi_delay(1);
    }

    if (timeout == 0)
        return RC522_ERR_TIMEOUT;

    bsp_spi_read(RC522_REG_FIFO_DATA, &tag_type[0]);
    bsp_spi_read(RC522_REG_FIFO_DATA, &tag_type[1]);

    return RC522_OK;
}

static rc522_status_t _rc522_anticoll(uint8_t *uid)
{
    uint8_t check = 0;

    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_IDLE);
    bsp_spi_write(RC522_REG_FIFO_LEVEL, 0x80);

    bsp_spi_write(RC522_REG_FIFO_DATA, PICC_CMD_ANTICOLL_CL1);
    bsp_spi_write(RC522_REG_FIFO_DATA, 0x20);

    bsp_spi_write(RC522_REG_BIT_FRAMING, RC522_BIT_FRAMING_ANTICOLL);

    bsp_spi_write(RC522_REG_COMMAND, RC522_CMD_TRANSCEIVE);
    bsp_spi_write(RC522_REG_BIT_FRAMING, RC522_BIT_START_SEND);

    bsp_spi_delay(5);

    int timeout = 100;
    uint8_t irq;

    while (timeout--)
    {
        bsp_spi_read(RC522_REG_COMM_IRQ, &irq);
        if (irq & 0x30)
            break;

        bsp_spi_delay(1);
    }

    if (timeout == 0)
        return RC522_ERR_TIMEOUT;

    for (int i = 0; i < 5; i++)
        bsp_spi_read(RC522_REG_FIFO_DATA, &uid[i]);

    for (int i = 0; i < 4; i++)
        check ^= uid[i];

    if (check != uid[4])
        return RC522_ERR_BCC_MISMATCH;

    return RC522_OK;
}
