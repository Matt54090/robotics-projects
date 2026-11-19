# STM32 LED PWM Layered Architecture

Layered embedded example for LED brightness control using PWM on STM32.

Architecture strictly enforces:

app → devices → bsp → HAL

HAL is accessed only inside BSP.


## Target

-   MCU: STM32F407VG
-   PWM Frequency: 1 kHz
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc
-   Optional: Native UNIT_TEST build (mock HAL)


## Directory Structure

common/ → Enums and shared definitions\
bsp/ → HAL abstraction (PWM + time)\
devices/ → LED driver\
app/ → Application logic (breathing control)\


## PWM Configuration

Recommended timer configuration:

-   Prescaler = 83\
-   ARR = 999\
-   PWM Mode = 1\
-   1 tick = 1 µs\
-   Frequency = 1 kHz


## Setup

1.  Open simple.ioc in CubeMX\
2.  Configure:
    -   TIM3 → PWM CH1 (or selected timer)
    -   Toolchain → Makefile
3.  Generate base project

Copy folders:

```
common/
bsp/
devices/
app/
```

into the generated project root.


## main.c (USER CODE section)

```
#include "app_led.h"

app_led_ctx_t led_ctx;

app_led_init(&led_ctx);

while (1)
{
    app_led_run(&led_ctx);
}
```


## Build (STM32)

```
$ make -j$(nproc)
```


## UNIT_TEST Build (Native)

Compile with:

```
-DUNIT_TEST
```

This replaces STM32 HAL with mock implementations and allows native
compilation on Ubuntu.


## Design Rules

-   No global variables
-   No magic numbers (all enums)
-   HAL used only in BSP
-   Devices never include HAL
-   App contains only state logic

This structure scales to multi-device embedded systems.
