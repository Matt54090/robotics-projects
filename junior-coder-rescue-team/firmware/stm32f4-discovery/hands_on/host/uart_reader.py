#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

###############################################################################
# UartReader class

import serial


class UartReader:
    """UART reader class"""

    def __init__(self, port: str, baud: int) -> None:
        self.__ser = serial.Serial(port, baud, timeout=1)

        if self.__ser.isOpen() is False:
            raise serial.SerialException(
                f"Failed to open {port} at {baud} baud"
            )

    def __del__(self) -> None:
        if hasattr(self, "_UartReader__ser"):
            try:
                self.__ser.close()
            except AttributeError:
                pass

    ###########################################################################
    # Public methods
    def parse_packet(self, packet: bytes) -> None:
        """Parse a packet and print its contents"""
        if len(packet) != 8:
            return

        if packet[0] != 0xAA or packet[7] != 0x55:
            return

        type_ = packet[1]
        data = int.from_bytes(packet[2:6], "big")

        checksum = packet[6]
        calc = packet[1] ^ packet[2] ^ packet[3] ^ packet[4] ^ packet[5]

        if checksum != calc:
            print("Checksum error")
            return

        if type_ == 0x01:
            print(f"[DOOR] Open (dist={data}cm)")

        elif type_ == 0x02:
            print(f"[IMU] ALERT (accel={data/100:.2f}g)")

        elif type_ == 0x03:
            print(f"[BAT] LOW ({data/100:.2f}V)")

        else:
            print(f"[UNKNOWN] type={type_} data={data}")

    def read_packet(self) -> bytes | None:
        """Read a packet from the UART and return it"""
        data = self.__ser.read(1)

        if not data:
            return None

        if data[0] == 0xAA:
            packet = data + self.__ser.read(7)
            self.parse_packet(packet)
            return packet

        return None


if __name__ == "__main__":
    uart = UartReader("/dev/ttyUSB0", 115200)

    print("Listening UART...")

    try:
        while True:
            pkt = uart.read_packet()

    #            if pkt is not None:
    #                print(f"Received packet: {pkt.hex()}")

    except KeyboardInterrupt:
        print("Exiting...")
