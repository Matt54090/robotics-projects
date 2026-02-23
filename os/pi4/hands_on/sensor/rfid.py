#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import time

from pirc522 import RFID  # pylint: disable=import-error

from common.gpio_mode import GpioMode


###############################################################################
#  Rfid class
class Rfid:
    """RFID class"""

    def __init__(self, bus: int, device: int, speed: int) -> None:
        self.__rfid = RFID(
            bus=bus,
            device=device,
            speed=speed,
            pin_rst=GpioMode.DUMMY_RFID_RST,
            pin_irq=None,
        )
        self.__util = self.__rfid.util()

    def __del__(self) -> None:
        if hasattr(self, "_Rfid__rfid"):
            try:
                self.__rfid.cleanup()
            except AttributeError:
                pass

    ###########################################################################
    # Public methods
    def get_uid(self) -> tuple[bool, list[int]]:
        """Get the UID of the RFID tag"""
        (err_req, _tag_type) = self.__rfid.request()
        if err_req:
            return (False, [])

        (err_uid, uid) = self.__rfid.anticoll()
        if err_uid:
            return (False, [])

        self.__util.deauth()
        return (True, uid)


if __name__ == "__main__":
    try:
        rfid = Rfid(
            GpioMode.SPI_BUS, GpioMode.SPI_DEVICE, GpioMode.SPI_MAX_SPEED_HZ
        )
        while True:
            (success, rfid_uid) = rfid.get_uid()
            if success:
                print(f"UID: {rfid_uid}")

            time.sleep(1)

        print("[JCRT] rfid test done!")

    except KeyboardInterrupt:
        print("[JCRT] rfid exit!")
