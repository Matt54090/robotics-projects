/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_SPI_H
#define COMMON_SPI_H

#include <stdint.h>

#define RC522_SOFT_RESET 0x0F

#define RC522_TIMER_MODE 0x8D
#define RC522_TIMER_PRESCALER 0x3E
#define RC522_TIMER_RELOAD_L 30
#define RC522_TIMER_RELOAD_H 0

#define RC522_TXASK_ENABLE 0x40
#define RC522_MODE_DEFAULT 0x3D

#define RC522_ANTENNA_ON 0x03

#define RC522_BIT_FRAMING_REQA 0x87
#define RC522_BIT_FRAMING_ANTICOLL 0x00
#define RC522_BIT_START_SEND 0x80

typedef enum {
    RC522_REG_COMMAND = 0x01,
    RC522_REG_COMM_IRQ = 0x04,
    RC522_REG_FIFO_DATA = 0x09,
    RC522_REG_FIFO_LEVEL = 0x0A,
    RC522_REG_BIT_FRAMING = 0x0D,
    RC522_REG_TX_CONTROL = 0x14,
    RC522_REG_TMODE = 0x2A,
    RC522_REG_TPRESCALER = 0x2B,
    RC522_REG_TRELOAD_H = 0x2C,
    RC522_REG_TRELOAD_L = 0x2D,
    RC522_REG_TX_ASK = 0x15,
    RC522_REG_MODE = 0x11,
    RC522_REG_VERSION = 0x37,
} rc522_reg_e;

typedef enum {
    RC522_CMD_IDLE = 0x00,
    RC522_CMD_TRANSCEIVE = 0x0C,
    RC522_CMD_SOFT_RESET = 0x0F,
} rc522_cmd_e;

typedef enum {
    PICC_CMD_REQA = 0x26,
    PICC_CMD_ANTICOLL_CL1 = 0x93,
} rc522_picc_cmd_e;

typedef enum {
    RC522_OK = 0,

    RC522_ERR_TIMEOUT = -1,
    RC522_ERR_NO_CARD = -2,
    RC522_ERR_BCC_MISMATCH = -3,
    RC522_ERR_INVALID_ATQA = -4,
    RC522_ERR_INVALID_UID = -5,

} rc522_status_t;

typedef struct {
    uint8_t uid[5];
    uint8_t uid_len;

    uint8_t atqa[2];

    uint8_t valid;
} rc522_uid_t;

#endif /* COMMON_SPI_H */
