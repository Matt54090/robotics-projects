#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

from RPi import GPIO  # pylint: disable=import-error


###############################################################################
#  Infrared class
class Infrared:
    """Infrared Class"""

    def __init__(self, pin: int) -> None:
        self.__pin = pin
        GPIO.setup(self.__pin, GPIO.IN)

    def __del__(self) -> None:
        if hasattr(self, "_Infrared__pin"):
            try:
                GPIO.setup(self.__pin, GPIO.IN)
            except RuntimeError:
                pass

    ###########################################################################
    # Public methods
    def is_obstacle_detected(self) -> bool:
        """Check if an obstacle is detected"""
        return GPIO.input(self.__pin) == 0
