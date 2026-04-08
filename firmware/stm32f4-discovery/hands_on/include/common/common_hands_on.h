/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_HANDS_ON_H
#define COMMON_HANDS_ON_H

#include <stdint.h>

#define TIMEOUT 100

typedef enum {
    SYSTEM_STATE_IDLE = 0,
    SYSTEM_STATE_DOOR_OPEN,
    SYSTEM_STATE_ALERT
} system_state_e;

typedef enum {
    EVENT_NONE = 0,
    EVENT_ULTRASONIC,
    EVENT_IMU
} system_event_e;

typedef enum {
    LED_RED = 0,
    LED_YELLOW,
    LED_GREEN,
} led_e;

typedef enum {
    PROTOCOL_DOOR_OPEN = 0x01,
    PROTOCOL_IMU_ALERT = 0x03
} protocol_e;

typedef enum {
    RETURN_TIMEOUT = -3,
    RETURN_BUSY,
    RETURN_ERROR,
    RETURN_OK,
} return_code_e;

void dev_delay_ms(uint32_t ms);
uint32_t dev_get_tick(void);

void bsp_delay_ms(uint32_t ms);
uint32_t bsp_get_tick(void);

#endif /* COMMON_HANDS_ON_H */
