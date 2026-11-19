/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include "app_timer.h"

#include "dev_timer.h"

#ifdef UNIT_TEST
#include <stdio.h>
#define dev_printf printf
#else
#include "dev_uart.h"
#endif

void app_timer_init(void)
{
    dev_timer_init();
}

void app_timer_run(void)
{
    static uint32_t last = 0;

    if (dev_timer_get_tick() - last > 60)
    {
        last = dev_timer_get_tick();
        dev_timer_trigger();
    }

    float dist = dev_timer_read_distance();

    if (dist > 0)
        dev_printf("[ULTRA] %.2f cm\n\r", dist);
}
