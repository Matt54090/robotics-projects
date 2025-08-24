#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import time
from enum import Enum

from smbus2 import SMBus  # pylint: disable=import-error


###############################################################################
#  Uart class
class Mpu6050Register(Enum):
    """Enum for MPU6050 registers"""

    I2C_ADDR = 0x68
    WHO_AM_I = 0x75
    PWR_MGMT_1 = 0x6B
    ACCEL_X = 0x3B
    ACCEL_Y = 0x3D
    ACCEL_Z = 0x3F
    GYRO_X = 0x43
    GYRO_Y = 0x45
    GYRO_Z = 0x47


class Mpu6050:
    """mpu6050 class"""

    ACCEL_SCALE = 16384.0  # when ±2g, LSB/g
    GYRO_SCALE = 131.0  # when ±250dps, LSB/(deg/s)

    def __init__(self, bus: int = 1) -> None:
        # get the i2c bus
        self.__bus = SMBus(bus)

        # wake up the MPU6050
        self.__bus.write_byte_data(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.PWR_MGMT_1, 0x00
        )

    def __del__(self) -> None:
        self.__bus.close()

    ###########################################################################
    # Public methods
    def read_who_am_i(self) -> int:
        """Read WHO_AM_I register"""
        return self.__bus.read_byte_data(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.WHO_AM_I
        )

    def read_accel_value(self) -> tuple[float, float, float]:
        """Read accelerometer values in g"""
        acc_x = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.ACCEL_X
        )
        acc_y = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.ACCEL_Y + 2
        )
        acc_z = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.ACCEL_Z + 4
        )

        return (
            acc_x / Mpu6050.ACCEL_SCALE,
            acc_y / Mpu6050.ACCEL_SCALE,
            acc_z / Mpu6050.ACCEL_SCALE,
        )

    def read_gyro_value(self) -> tuple[float, float, float]:
        """Read gyroscope values in degrees per second"""
        gyro_x = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.GYRO_X
        )
        gyro_y = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.GYRO_Y + 2
        )
        gyro_z = self.__read_word(
            Mpu6050Register.I2C_ADDR, Mpu6050Register.GYRO_Z + 4
        )

        return (
            gyro_x / Mpu6050.GYRO_SCALE,
            gyro_y / Mpu6050.GYRO_SCALE,
            gyro_z / Mpu6050.GYRO_SCALE,
        )

    ###########################################################################
    # Internal methods
    def __read_word(self, addr: int, reg: int) -> int:
        hi_data = self.__bus.read_byte_data(addr, reg)
        lo_data = self.__bus.read_byte_data(addr, reg + 1)

        value = (hi_data << 8) | lo_data
        if value & 0x8000:
            value -= 65536

        return value


if __name__ == "__main__":
    mpu = Mpu6050()
    print(f"[JCRT] WHO AM I: {mpu.read_who_am_i()}")

    try:
        while True:
            ax, ay, az = mpu.read_accel_value()
            gx, gy, gz = mpu.read_gyro_value()

            print(
                f"ACCEL: x={ax:6d} y={ay:6d} z={az:6d} | "
                f"GYRO: x={gx:6d} y={gy:6d} z={gz:6d}"
            )

            time.sleep(0.2)
    except KeyboardInterrupt:
        print("[JCRT] Exit the i2c.py!")
