#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

Copyright (c) 2025 Junior Coder Rescue Team
(junior.coder.rescue.team@gmail.com)

See the LICENSE file in the project root for more details.
"""

from enum import Enum


class Delay(Enum):
    """Delay Durations Enumeration"""

    RFID_DETECT = 2.0
    WAIT_FOR_START = 0.5
    CHECK_OBSTACLE = 0.2
    TURN_DURATION = 1.0
    MAIN_LOOP = 0.1
    OBSTACLE_LOOP = 0.3
