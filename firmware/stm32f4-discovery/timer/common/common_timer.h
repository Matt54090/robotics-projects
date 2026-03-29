/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#ifndef COMMON_TIMER_H
#define COMMON_TIMER_H

#include <stdint.h>

#define TIMER_TIMEOUT_US 30000
#define SOUND_SPEED_CM_PER_US 0.0343f

static inline float timer_us_to_distance(uint32_t us)
{
    return (us * SOUND_SPEED_CM_PER_US) / 2.0f;
}

#endif /* COMMON_TIMER_H */
