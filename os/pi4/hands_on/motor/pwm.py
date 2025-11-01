#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

from RPi import GPIO  # pylint: disable=import-error


###############################################################################
#  Pwm class
class Pwm:
    """Pwm Class"""

    def __init__(self, left_dir_pin: int, left_motor_pin: int,
                 right_dir_pin: int, right_motor_pin: int) -> None:
        self.__left_dir = left_dir_pin
        self.__left_motor = left_motor_pin
        self.__right_dir = right_dir_pin
        self.__right_motor = right_motor_pin

        GPIO.setup(self.__left_dir, GPIO.OUT)
        GPIO.setup(self.__left_motor, GPIO.OUT)
        GPIO.setup(self.__right_dir, GPIO.OUT)
        GPIO.setup(self.__right_motor, GPIO.OUT)

        GPIO.output(self.__left_dir, GPIO.HIGH)
        GPIO.output(self.__right_dir, GPIO.LOW)

        self.__pwm_l = GPIO.PWM(self.__left_motor, 1000)
        self.__pwm_r = GPIO.PWM(self.__right_motor, 1000)

        self.__pwm_l.start(0)
        self.__pwm_r.start(100)

    def __del__(self) -> None:
        self.stop_all()

        self.__pwm_r.stop()
        self.__pwm_l.stop()
        del self.__pwm_r, self.__pwm_l

        GPIO.output(self.__right_dir, GPIO.LOW)
        GPIO.output(self.__left_dir, GPIO.HIGH)

        GPIO.setup(self.__right_motor, GPIO.IN)
        GPIO.setup(self.__right_dir, GPIO.IN)
        GPIO.setup(self.__left_motor, GPIO.IN)
        GPIO.setup(self.__left_dir, GPIO.IN)

    ###########################################################################
    # Public methods
    def stop_all(self) -> None:
        """Stop all motors"""
        self.__pwm_l.ChangeDutyCycle(0)
        self.__pwm_r.ChangeDutyCycle(0)

    def move_forward(self, speed: int = 10) -> None:
        """Move forward"""
        GPIO.output(self.__left_dir, GPIO.HIGH)
        GPIO.output(self.__right_dir, GPIO.LOW)
        self.__pwm_l.ChangeDutyCycle(speed)
        self.__pwm_r.ChangeDutyCycle(100 - speed)

    def move_backward(self, speed: int = 60) -> None:
        """Move backward"""
        GPIO.output(self.__left_dir, GPIO.LOW)
        GPIO.output(self.__right_dir, GPIO.HIGH)
        self.__pwm_l.ChangeDutyCycle(100 - speed)
        self.__pwm_r.ChangeDutyCycle(speed)
