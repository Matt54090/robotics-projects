#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import random
import time

from RPi import GPIO  # pylint: disable=import-error

from common.gpio_mode import GpioMode
from motor.pwm import Pwm
from sensor.imu import Imu
from sensor.infrared import Infrared
from sensor.led import Led
from sensor.rfid import Rfid


###############################################################################
class Robot:
    """Autonomous obstacle-avoiding robot with LED + IMU logging"""

    def __init__(self) -> None:
        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)

        self.__rfid = Rfid(
            GpioMode.SPI_BUS, GpioMode.SPI_DEVICE, GpioMode.SPI_MAX_SPEED_HZ
        )

        # in RFID packages, setmode called multiple times,
        # so we need to reset here
        GPIO.cleanup()
        GPIO.setmode(GPIO.BCM)

        # Private devices
        self.__infrared = Infrared(GpioMode.SEN_INFRARED)
        self.__led = Led(
            GpioMode.LED_RED, GpioMode.LED_YELLOW, GpioMode.LED_GREEN
        )
        self.__motor = Pwm(
            GpioMode.DIR_LEFT_MOTOR,
            GpioMode.PWM_LEFT_MOTOR,
            GpioMode.DIR_RIGHT_MOTOR,
            GpioMode.PWM_RIGHT_MOTOR,
        )
        self.__imu = Imu(GpioMode.I2C_BUS)

        self.__running = False
        self.__loop_interval = 0.1

    def __del__(self) -> None:
        self.stop()
        GPIO.cleanup()

    ###########################################################################
    # Public methods
    def start(self) -> None:
        """Robot main entry"""
        print("[JCRT] Start robot!")
        self.__wait_for_start()
        self.__main_loop()

    def stop(self) -> None:
        """Stop and cleanup"""
        print("[JCRT] Stopping robot...")
        self.__motor.stop_all()
        self.__running = False

    ###########################################################################
    # Internal methods
    def __wait_for_start(self) -> None:
        """RFID standby state with yellow LED blinking"""
        print("[JCRT] Waiting for RFID card...")
        while True:
            detected, uid = self.__rfid.get_uid()
            if detected:
                print(f"[JCRT] RFID detected: UID={uid}")
                self.__led.set_red()
                self.__led.set_green()
                self.__led.set_yellow()

                time.sleep(2.0)
                self.__led.clear_yellow()
                self.__running = True
                break

            # Blink yellow LED while waiting
            self.__led.set_yellow()
            time.sleep(0.5)
            self.__led.clear_yellow()
            time.sleep(0.5)

    def __main_loop(self) -> None:
        """Main motion + IMU logging loop"""
        print("[JCRT] Robot moving...")
        while self.__running:
            if not self.__infrared.is_obstacle_detected():
                self.__led.set_green()
                self.__motor.move_forward(60)
                self.__log_imu()
            else:
                self.__handle_obstacle()
            time.sleep(self.__loop_interval)

    def __handle_obstacle(self) -> None:
        """Obstacle detected sequence"""
        print("[JCRT] Obstacle detected!")
        self.__motor.stop_all()
        self.__led.clear_green()
        self.__led.set_red()

        # Blink yellow for 0.5 seconds
        print("[JCRT] Pausing... blinking yellow")
        end_time = time.time() + 0.5
        while time.time() < end_time:
            self.__led.set_yellow()
            time.sleep(0.2)
            self.__led.clear_yellow()
            time.sleep(0.2)

        # Random turn
        action = random.choice(["left", "right"])
        print(f"[JCRT] Avoiding → {action}")
        if action == "left":
            self.__motor.turn_left()
            time.sleep(0.4)
        elif action == "right":
            self.__motor.turn_right()
            time.sleep(0.4)

        self.__motor.stop_all()
        self.__led.clear_red()
        self.__led.clear_yellow()
        time.sleep(0.3)

    def __log_imu(self) -> None:
        """Log accelerometer and gyro data"""
        acc = self.__imu.read_accel_value()
        gyro = self.__imu.read_gyro_value()
        print(
            f"[IMU] Accel(g): x={acc[0]:.2f}, y={acc[1]:.2f}, z={acc[2]:.2f} |"
            f" Gyro(dps): x={gyro[0]:.1f}, y={gyro[1]:.1f}, z={gyro[2]:.1f}"
        )


def main() -> None:
    """Program entry"""
    robot = Robot()
    try:
        robot.start()
    except KeyboardInterrupt:
        print("\n[JCRT] Interrupted by user")
    finally:
        robot.stop()


if __name__ == "__main__":
    main()
