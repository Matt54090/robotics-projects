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
#  Led class
class Led:
    """Led Class"""

    def __init__(self, red_pin: int, yello_pin: int, green_pin: int) -> None:
        self.__red_pin = red_pin
        self.__yello_pin = yello_pin
        self.__green_pin = green_pin

        GPIO.setup(self.__red_pin, GPIO.OUT)
        GPIO.setup(self.__yello_pin, GPIO.OUT)
        GPIO.setup(self.__green_pin, GPIO.OUT)

        GPIO.output(self.__red_pin, GPIO.LOW)
        GPIO.output(self.__yello_pin, GPIO.LOW)
        GPIO.output(self.__green_pin, GPIO.LOW)

    def __del__(self) -> None:
        for attr in ("_Led__green_pin", "_Led__yello_pin", "_Led__red_pin"):
            if hasattr(self, attr):
                try:
                    pin = getattr(self, attr)
                    GPIO.output(pin, GPIO.LOW)
                    GPIO.setup(pin, GPIO.IN)
                except RuntimeError:
                    pass

    ###########################################################################
    # Public methods
    def set_red(self) -> None:
        """Set LED to Red"""
        GPIO.output(self.__red_pin, GPIO.HIGH)

    def set_yellow(self) -> None:
        """Set LED to Yellow"""
        GPIO.output(self.__yello_pin, GPIO.HIGH)

    def set_green(self) -> None:
        """Set LED to Green"""
        GPIO.output(self.__green_pin, GPIO.HIGH)

    def clear_red(self) -> None:
        """Clear Red LED"""
        GPIO.output(self.__red_pin, GPIO.LOW)

    def clear_yellow(self) -> None:
        """Clear Yellow LED"""
        GPIO.output(self.__yello_pin, GPIO.LOW)

    def clear_green(self) -> None:
        """Clear Green LED"""
        GPIO.output(self.__green_pin, GPIO.LOW)

    def clear_all(self) -> None:
        """Clear All LEDs"""
        self.clear_red()
        self.clear_yellow()
        self.clear_green()

    def blink_yellow(self, interval: float) -> None:
        """Blink Yellow LED"""
        self.set_yellow()
        time.sleep(interval)
        self.clear_yellow()
        time.sleep(interval)

    def on_and_off(self, interval: float) -> None:
        """Blink All LEDs"""
        self.set_red()
        self.set_yellow()
        self.set_green()
        time.sleep(interval)

        self.clear_red()
        self.clear_yellow()
        self.clear_green()
