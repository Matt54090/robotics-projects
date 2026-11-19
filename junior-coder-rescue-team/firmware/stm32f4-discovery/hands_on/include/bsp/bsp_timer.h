/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include <stdint.h>

int bsp_timer_init(void);
int bsp_timer_trigger(void);
int bsp_timer_get_pulse(uint32_t *pulse);

#endif /* BSP_TIMER_H */
