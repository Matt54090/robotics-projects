# STM32 SG90 PWM Layered Template

Layered architecture example for controlling an SG90 servo using PWM on
STM32.

Base STM32 project must be generated with CubeMX.


## Target

-   MCU: STM32F407VG
-   Servo: SG90
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc


## Repository Structure

```
app/ → Application logic
bsp/ → HAL abstraction (TIM, Time)
devices/ → Servo driver
common/ → Enums and board config
simple.ioc → CubeMX configuration
```


## PWM Settings (SG90)

SG90 requires:

-   50Hz PWM (20ms period)
-   1ms → 0°
-   1.5ms → 90°
-   2ms → 180°

Recommended timer config:

-   Prescaler = 83
-   ARR = 19999
-   PWM Mode = 1
-   1 tick = 1µs


## Setup

1.  Open simple.ioc in CubeMX
2.  Configure:
    -   TIM4 → PWM CH2
    -   PB7 → TIM4_CH2
    -   Toolchain → Makefile
3.  Generate Code

Copy these folders into the project root:

```
app/
bsp/
devices/
common/
```


## main.c

Inside USER CODE sections:

```
#include "app_pwm.h"

app_servo_ctx_t servo_ctx;

app_pwm_init(&servo_ctx);

while (1)
{
    app_pwm_run(&servo_ctx);
}
```


## Build

```
$ make -j$(nproc)
```


## Architecture Rules

-   Only BSP calls HAL
-   Devices use BSP only
-   App uses Devices only
-   No business logic in main.c


## UNIT_TEST

Build with:

```
-DUNIT_TEST
```

This replaces STM32 HAL with dummy implementations for CI/native
compilation.
