/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "devices/dev_ultrasonic.h"

#include "bsp/bsp_timer.h"
#include "common/common_hands_on.h"

#define SOUND_SPEED 0.034f
#define TIMEOUT_MS 50

void dev_ultrasonic_init(void)
{
    bsp_timer_init();
}

int dev_ultrasonic_read_cm(uint32_t *distance)
{
    uint32_t pulse;
    uint32_t start = bsp_get_tick();

    bsp_timer_trigger();

    while (bsp_timer_get_pulse(&pulse) != 0)
    {
        if ((bsp_get_tick() - start) > TIMEOUT_MS)
            return RETURN_ERROR;
    }

    float dist = (pulse * SOUND_SPEED) / 2.0f;
    *distance = (uint32_t)dist;
    return 0;
}

int dev_ultrasonic_detect(void)
{
    uint32_t distance;

    if (dev_ultrasonic_read_cm(&distance) != 0)
        return RETURN_ERROR;

    if (distance < 10)
        return RETURN_OK;

    return RETURN_ERROR;
}
