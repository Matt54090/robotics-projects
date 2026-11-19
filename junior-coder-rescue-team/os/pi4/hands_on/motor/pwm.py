#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import time

from RPi import GPIO  # pylint: disable=import-error


###############################################################################
#  Pwm class
class Pwm:
    """Pwm Class"""

    def __init__(
        self,
        left_dir_pin: int,
        left_motor_pin: int,
        right_dir_pin: int,
        right_motor_pin: int,
    ) -> None:
        self.__left_dir = left_dir_pin
        self.__left_motor = left_motor_pin
        self.__right_dir = right_dir_pin
        self.__right_motor = right_motor_pin

        GPIO.setup(self.__left_dir, GPIO.OUT)
        GPIO.setup(self.__left_motor, GPIO.OUT)
        GPIO.setup(self.__right_dir, GPIO.OUT)
        GPIO.setup(self.__right_motor, GPIO.OUT)

        GPIO.output(self.__left_dir, GPIO.LOW)
        GPIO.output(self.__right_dir, GPIO.HIGH)

        self.__pwm_l = GPIO.PWM(self.__left_motor, 1000)
        self.__pwm_r = GPIO.PWM(self.__right_motor, 1000)

        self.__pwm_l.start(0)
        self.__pwm_r.start(100)

    def __del__(self) -> None:
        cls_prefix = f"_{self.__class__.__name__}__"
        pwm_attrs = [cls_prefix + "pwm_l", cls_prefix + "pwm_r"]
        gpio_attrs = [
            cls_prefix + "left_dir",
            cls_prefix + "left_motor",
            cls_prefix + "right_dir",
            cls_prefix + "right_motor",
        ]

        for attr in pwm_attrs:
            if hasattr(self, attr):
                pwm_attr = getattr(self, attr)
                try:
                    pwm_attr.ChangeDutyCycle(0)
                    pwm_attr.stop()
                except (RuntimeError, ValueError):
                    pass

        for attr in gpio_attrs:
            if hasattr(self, attr):
                try:
                    pin = getattr(self, attr)
                    GPIO.output(pin, GPIO.LOW)
                    GPIO.setup(pin, GPIO.IN)
                except RuntimeError:
                    pass

    ###########################################################################
    # Public methods
    def stop_all(self) -> None:
        """Stop all motors"""
        GPIO.output(self.__left_dir, GPIO.LOW)
        GPIO.output(self.__right_dir, GPIO.HIGH)
        self.__pwm_l.ChangeDutyCycle(0)
        self.__pwm_r.ChangeDutyCycle(100)

    def move_forward(self, speed: int = 50) -> None:
        """Move forward"""
        GPIO.output(self.__left_dir, GPIO.LOW)
        GPIO.output(self.__right_dir, GPIO.HIGH)
        self.__pwm_l.ChangeDutyCycle(speed)
        self.__pwm_r.ChangeDutyCycle(100 - speed)

    def turn_left(self, speed: int = 50, interval: float = 1.0) -> None:
        """Turn left"""
        GPIO.output(self.__left_dir, GPIO.HIGH)
        GPIO.output(self.__right_dir, GPIO.HIGH)
        self.__pwm_l.ChangeDutyCycle(100 - speed)
        self.__pwm_r.ChangeDutyCycle(100 - speed)
        time.sleep(interval)
        self.stop_all()

    def turn_right(self, speed: int = 50, interval: float = 1.0) -> None:
        """Turn right"""
        GPIO.output(self.__left_dir, GPIO.LOW)
        GPIO.output(self.__right_dir, GPIO.LOW)
        self.__pwm_l.ChangeDutyCycle(speed)
        self.__pwm_r.ChangeDutyCycle(speed)
        time.sleep(interval)
        self.stop_all()


if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    try:
        pwm = Pwm(5, 12, 6, 13)
        pwm.move_forward(75)
        time.sleep(2)

        pwm.turn_left(speed=60, interval=1.0)
        time.sleep(2)

        pwm.turn_right(speed=60, interval=1.0)
        time.sleep(2)

        print("[JCRT] pwm test done!")
    except KeyboardInterrupt:
        print("[JCRT] pwm exit!")
    finally:
        GPIO.cleanup()
