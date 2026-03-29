/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "dev_timer.h"

#include "bsp_timer.h"
#include "common_timer.h"

int dev_timer_init(void)
{
    return bsp_timer_init();
}

void dev_timer_trigger(void)
{
    bsp_timer_trigger();
}

float dev_timer_read_distance(void)
{
    uint32_t us = 0;

    if (bsp_timer_get_pulse(&us) < 0)
        return -1.0f;

    if (us < 100 || us > 30000)
        return -1.0f;

    return timer_us_to_distance(us);
}

uint32_t dev_timer_get_tick(void)
{
    return bsp_timer_get_tick();
}
