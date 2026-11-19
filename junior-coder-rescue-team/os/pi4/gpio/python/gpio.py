#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""


import time

from RPi import GPIO

GPIO.setmode(GPIO.BCM)

IO_PORT = 18
GPIO.setup(IO_PORT, GPIO.OUT)

try:
    while True:
        GPIO.output(IO_PORT, GPIO.HIGH)
        print("[JCRT] GPIO set!")
        time.sleep(1)

        GPIO.output(IO_PORT, GPIO.LOW)
        print("[JCRT] GPIO clear.")
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.output(IO_PORT, GPIO.LOW)
    GPIO.cleanup()
    print("[JCRT] Exit the gpio.py!")
