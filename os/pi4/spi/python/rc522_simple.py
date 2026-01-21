#!/usr/bin/env python3
# pylint: disable=import-error
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import spidev

spi = spidev.SpiDev()
spi.open(0, 0)  # bus 0, device 0 (/dev/spidev0.0)
spi.max_speed_hz = 1_000_000
spi.mode = 0


def read_reg(addr):
    """Read a register from RC522 via SPI"""
    # 7bit address + 0x80(read) + dummy
    val = spi.xfer2([((addr << 1) & 0x7E) | 0x80, 0])
    return val[1]


version = read_reg(0x37)
print("RC522 Version:", hex(version))
