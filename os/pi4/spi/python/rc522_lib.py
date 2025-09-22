#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import time

from pirc522 import RFID
from RPi import GPIO

if __name__ == "__main__":
    GPIO.setwarnings(False)
    rdr = RFID(pin_rst=22, pin_irq=None)
    util = rdr.util()
    util.debug = False

    try:
        print("[JCRT] Press tag on the reader to check...")
        while True:
            (err_req, tag_type) = rdr.request()
            if not err_req:
                (err_uid, uid) = rdr.anticoll()
                if not err_uid:
                    print(f"[TAG] Type={tag_type} | UID={uid}")
                    util.deauth()

            time.sleep(0.1)
    except KeyboardInterrupt:
        print("[JCRT] Exit the spi.py!")
    finally:
        rdr.cleanup()
