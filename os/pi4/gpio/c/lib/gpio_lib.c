/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Junior Coder Rescue Team
 * (junior.coder.rescue.team@gmail.com)
 *
 * See the LICENSE file in the project root for more details.
 */

#include <errno.h>
#include <pigpio.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

enum {
    OFF,
    ON,
    IO_PORT = 18
};

static void _handler_for_ctrl_c(int signo);
static inline int _check_permission(void);

static int g_escape = OFF;

int main(void)
{
    if (_check_permission() < 0)
    {
        fprintf(stderr, "[JCRT ERR] Need to execute as root!\n");
        return -EPERM;
    }

    struct sigaction sig_act = {
        .sa_handler = _handler_for_ctrl_c,
        .sa_flags = 0,
    };
    sigemptyset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);

    if (gpioInitialise() < 0)
    {
        fprintf(stderr, "[JCRT ERR] failed init for pigpio.\n");
        return -EPERM;
    }

    gpioSetMode(IO_PORT, PI_OUTPUT);

    while (g_escape == OFF)
    {
        gpioWrite(IO_PORT, ON);
        printf("[JCRT] GPIO set!\n");
        sleep(1);

        gpioWrite(IO_PORT, OFF);
        printf("[JCRT] GPIO clear.\n");
        sleep(1);
    }

    gpioWrite(IO_PORT, OFF);
    gpioTerminate();
    printf("[JCRT] Exit the gpio_lib.c\n");

    return 0;
}

static void _handler_for_ctrl_c(int signo)
{
    (void)signo;

    g_escape = ON;
}

static inline int _check_permission(void)
{
    if (getuid() == 0 || geteuid() == 0)
        return 0;

    return -EPERM;
}
