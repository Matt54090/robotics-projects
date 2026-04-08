/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_LED_H
#define DEV_LED_H

#include "common/common_hands_on.h"

void dev_led_init(void);
void dev_led_set(led_e led, int on);
void dev_led_blink(led_e led);

#endif /* DEV_LED_H */
