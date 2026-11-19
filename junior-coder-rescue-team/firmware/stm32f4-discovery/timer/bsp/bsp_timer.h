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
void bsp_timer_trigger(void);
int bsp_timer_get_pulse(uint32_t *pulse);

uint32_t bsp_timer_get_tick(void);

#endif /* BSP_TIMER_H */
