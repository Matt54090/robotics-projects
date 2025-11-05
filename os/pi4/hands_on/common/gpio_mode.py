#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

from enum import IntEnum


class GpioMode(IntEnum):
    """GPIO Modes Enumeration"""

    SEN_INFRARED = 17

    LED_RED = 18
    LED_YELLOW = 27
    LED_GREEN = 22

    PWM_LEFT_MOTOR = 12
    PWM_RIGHT_MOTOR = 13

    DIR_LEFT_MOTOR = 5
    DIR_RIGHT_MOTOR = 6

    I2C_BUS = 1
    SPI_BUS = 0
    SPI_DEVICE = 0
    SPI_MAX_SPEED_HZ = 1_000_000

    DUMMY_RFID_RST = 22
