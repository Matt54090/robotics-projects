/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef DEV_TIMER_H
#define DEV_TIMER_H

#include <stdint.h>

int dev_timer_init(void);
void dev_timer_trigger(void);
float dev_timer_read_distance(void);

uint32_t dev_timer_get_tick(void);

#endif /* DEV_TIMER_H */
