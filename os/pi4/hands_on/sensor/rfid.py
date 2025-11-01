#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

from pirc522 import RFID  # pylint: disable=import-error


###############################################################################
#  Rfid class
class Rfid:
    """RFID class"""

    def __init__(self, pin_rst: int, pin_irq: int) -> None:
        self.__rfid = RFID(pin_rst=pin_rst, pin_irq=pin_irq)
        self.__util = self.__rfid.util()

    def __del__(self) -> None:
        self.__rfid.cleanup()

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
