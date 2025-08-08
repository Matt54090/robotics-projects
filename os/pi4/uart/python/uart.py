#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import sys
import threading
import time

import serial

###############################################################################
#  Uart class


class Uart:
    """ Uart Class """
    def __init__(self, baudrate: int = 115200) -> None:
        self.__serial = serial.Serial("/dev/ttyAMA2", baudrate=baudrate,
                                      timeout=1)
        if self.__serial.isOpen() is False:
            sys.exit(1)

        self.__escape = False

        self.__tx = threading.Thread(target=self.__transmitter, daemon=True)
        self.__rx = threading.Thread(target=self.__receiver, daemon=True)

        self.__tx.start()
        self.__rx.start()

        print("[UART] Init Uart!")

    def __del__(self) -> None:
        self.__tx.join()
        self.__rx.join()

        if self.__serial.isOpen():
            self.__serial.close()

        print("[UART] Exit Uart!")

    ###########################################################################
    # Public methods
    @property
    def escape(self) -> bool:
        """ Getter for escape """
        return self.__escape

    @escape.setter
    def escape(self, value: bool) -> None:
        """ Setter for escape """
        self.__escape = value

    ###########################################################################
    # Internal methods
    def __transmitter(self) -> None:
        while self.__escape is False:
            data = input("[JCRT] Enter the data: ")
            self.__serial.write((data + '\n').encode('utf-8'))
            print("[JCRT] Data Transmitted: ")

            time.sleep(1)

    def __receiver(self) -> None:
        while self.__escape is False:
            if self.__serial.in_waiting > 0:
                data = self.__serial.readline().decode('utf-8').strip()
                print(f"[JCRT] Data Received: {data}")

            time.sleep(1)


if __name__ == "__main__":
    uart = Uart()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        uart.escape = True
        print("[JCRT] Exit the Uart program.")
