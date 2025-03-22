/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <pigpio.h>
#include <signal.h>

#include <jcrt/common.h>

#define DEBUG

int main(void)
{
    FORMULA_GUARD(check_permission() < 0, -EPERM, "Need to execute as root!");

    struct sigaction sig_act = {
        .sa_handler = handler_for_ctrl_c,
        .sa_flags = 0,
    };
    sigemptyset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);

    FORMULA_GUARD(gpioInitialise() < 0, -EPERM, "Failed init for pigpio.");

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
