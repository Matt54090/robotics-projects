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
#  Mpu6050Register enum class
class Mpu6050Register(Enum):
    """Enum for MPU6050 registers"""

    I2C_ADDR = 0x68
    PWR_MGMT_1 = 0x6B
    ACCEL_X = 0x3B
    ACCEL_Y = 0x3D
    ACCEL_Z = 0x3F
    GYRO_X = 0x43
    GYRO_Y = 0x45
    GYRO_Z = 0x47


###############################################################################
#  Imu class
class Imu:
    """mpu6050 class"""

    ACCEL_SCALE = 16384.0  # when ±2g, LSB/g
    GYRO_SCALE = 131.0  # when ±250dps, LSB/(deg/s)

    def __init__(self, bus: int) -> None:
        # get the i2c bus
        self.__bus = SMBus(bus)

        # wake up the MPU6050
        self.__bus.write_byte_data(
            Mpu6050Register.I2C_ADDR.value,
            Mpu6050Register.PWR_MGMT_1.value,
            0x00,
        )

    def __del__(self) -> None:
        if hasattr(self, "_Imu__bus"):
            try:
                self.__bus.close()
            except AttributeError:
                pass

    ###########################################################################
    # Public methods
    def read_accel_value(self) -> tuple[float, float, float]:
        """Read accelerometer values in g"""
        acc_x = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.ACCEL_X.value
        )
        acc_y = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.ACCEL_Y.value
        )
        acc_z = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.ACCEL_Z.value
        )

        return (
            acc_x / Imu.ACCEL_SCALE,
            acc_y / Imu.ACCEL_SCALE,
            acc_z / Imu.ACCEL_SCALE,
        )

    def read_gyro_value(self) -> tuple[float, float, float]:
        """Read gyroscope values in degrees per second"""
        gyro_x = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.GYRO_X.value
        )
        gyro_y = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.GYRO_Y.value
        )
        gyro_z = self.__read_word(
            Mpu6050Register.I2C_ADDR.value, Mpu6050Register.GYRO_Z.value
        )

        return (
            gyro_x / Imu.GYRO_SCALE,
            gyro_y / Imu.GYRO_SCALE,
            gyro_z / Imu.GYRO_SCALE,
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
    imu = Imu(1)

    try:
        while True:
            acc = imu.read_accel_value()
            gyro = imu.read_gyro_value()

            print(
                f"Acc: X={acc[0]:.2f}, Y={acc[1]:.2f}, Z={acc[2]:.2f} |"
                f"Gyro: X={gyro[0]:.2f}, Y={gyro[1]:.2f}, Z={gyro[2]:.2f}"
            )

            time.sleep(0.2)

        print("[JCRT] imu test done!")
    except KeyboardInterrupt:
        print("[JCRT] imu exit!")
