/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <pigpio.h>

#include <jcrt/common.h>

#define DEBUG

int main(void)
{
    int ret = gpioInitialise();
    FORMULA_GUARD(ret < 0, -EPERM, "Failed init for pigpio.");

    ret = init_jcrt();
    FORMULA_GUARD(ret < 0, ret, "Failed init for JCRT!");

    gpioSetMode(IO_PORT, PI_OUTPUT);

    while (g_escape == OFF)
    {
        gpioWrite(IO_PORT, ON);
        DBG_MSG("GPIO set!");
        sleep(1);

        gpioWrite(IO_PORT, OFF);
        DBG_MSG("GPIO clear.");
        sleep(1);
    }

    gpioWrite(IO_PORT, OFF);
    gpioTerminate();
    DBG_MSG("Exit the gpio_lib.c");

    return 0;
}
