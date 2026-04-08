/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_ULTRASONIC_H
#define DEV_ULTRASONIC_H

#include <stdint.h>

void dev_ultrasonic_init(void);
int dev_ultrasonic_read_cm(uint32_t *distance);
int dev_ultrasonic_detect(void);

#endif /* DEV_ULTRASONIC_H */
