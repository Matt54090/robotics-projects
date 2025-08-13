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

int main(void)
{
    int ret = gpioInitialise();
    FORMULA_GUARD(ret < 0, -EPERM, "Failed to initialize pigpio.");

    ret = init_jcrt();
    FORMULA_GUARD(ret < 0, ret, "Failed to initialize jcrt.");

    gpioSetMode(IO_PORT, PI_ALT5);

    /* set the PWM configuration */
    int freq = 1000;   // Hz
    int duty = 500000; // 50% (range: 0 ~ 1,000,000)
    gpioHardwarePWM(IO_PORT, freq, duty);
    DBG_MSG("Start the PWM on GPIO %d port!", IO_PORT);

    int i, duty_cycle;
    while (g_escape == OFF)
    {
        /* Change the duty cycle from 0 to 1,000,000 */
        for (i = 0; i < 10; i++)
        {
            if (g_escape == ON)
                break;

            duty_cycle = (i * 100000);
            gpioHardwarePWM(IO_PORT, freq, duty_cycle);
            DBG_MSG("Set PWM duty cycle to %d", duty_cycle);
            sleep(1);
        }

        /* Change the duty cycle from 1,000,000 to 0 */
        for (i = 10; i > 0; i--)
        {
            if (g_escape == ON)
                break;

            duty_cycle = (i * 100000);
            gpioHardwarePWM(IO_PORT, freq, duty_cycle);
            DBG_MSG("Set PWM duty cycle to %d", duty_cycle);
            sleep(1);
        }
    }

    gpioHardwarePWM(IO_PORT, 0, 0);
    gpioSetMode(IO_PORT, PI_OUTPUT);
    gpioWrite(IO_PORT, 0);
    gpioTerminate();
    DBG_MSG("Exit the pwm_lib.c");

    return 0;
}
