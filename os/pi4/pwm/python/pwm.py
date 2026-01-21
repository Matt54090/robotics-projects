#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

import sys
import time

import pigpio  # pylint: disable=import-error

IO_PORT = 18  # GPIO18 (PWM0)

pi = pigpio.pi()
if not pi.connected:
    print("[JCRT ERR] Failed to connect to pigpio daemon.")
    sys.exit(1)

# set the GPIO to PWM
pi.set_mode(IO_PORT, pigpio.ALT5)

# set the PWM configuration
FREQ = 1000  # Hz
DUTY = 500000  # 50% (range: 0 ~ 1,000,000)
pi.hardware_PWM(IO_PORT, FREQ, DUTY)
print(f"[JCRT] Start the PWM on GPIO{IO_PORT} port!")

try:
    while True:
        for duty_cycle in range(0, 1000001, 100000):
            print(f"[JCRT] Set PWM duty cycle to {duty_cycle / 10000:.2f}%")
            pi.hardware_PWM(IO_PORT, FREQ, duty_cycle)
            time.sleep(0.5)

        for duty_cycle in range(1000000, -1, -100000):
            print(f"[JCRT] Set PWM duty cycle to {duty_cycle / 10000:.2f}%")
            pi.hardware_PWM(IO_PORT, FREQ, duty_cycle)
            time.sleep(0.5)

except KeyboardInterrupt:
    pi.hardware_PWM(IO_PORT, 0, 0)  # PWM off
    pi.set_mode(IO_PORT, pigpio.OUTPUT)
    pi.write(IO_PORT, 0)
    pi.stop()
    print("[JCRT] Exit the pwm.py!")
