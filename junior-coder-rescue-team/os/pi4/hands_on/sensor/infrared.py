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


if __name__ == "__main__":
    GPIO.setmode(GPIO.BCM)
    infrared = Infrared(17)

    try:
        while True:
            if infrared.is_obstacle_detected():
                print("Obstacle detected!")
            else:
                print("No obstacle detected.")

            time.sleep(1)

        print("[JCRT] infrared test done!")
    except KeyboardInterrupt:
        print("[JCRT] infrared exit!")
    finally:
        GPIO.cleanup()
