# STM32 Ultrasonic Sensor (HC-SR04) - Timer Input Capture Template

Layered architecture example for ultrasonic sensor using STM32 Timer
Input Capture.


## Target

-   MCU: STM32F407VG
-   Timer: TIM3 (Input Capture)
-   Pins:
    -   ECHO → PC8 (TIM3_CH3)
    -   TRIG → PC9 (GPIO)
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc


## Repository Structure

    app/      → Application logic
    bsp/      → HAL abstraction (Timer / GPIO)
    devices/  → Sensor device layer
    common/   → Constants / conversion
    simple.ioc → CubeMX configuration


## Behavior

-   Sends 10us trigger pulse
-   Captures echo pulse width using interrupt
-   Converts time → distance (cm)
-   Non-blocking (state machine based)


## CubeMX Configuration


### TIM3

-   Channel3 → Input Capture
-   Prescaler → 84 - 1 (1MHz → 1us resolution)
-   Period → 65535
-   NVIC → Enable TIM3 global interrupt


### GPIO

-   PC8 → Alternate Function (TIM3_CH3), Pull-down
-   PC9 → Output Push-Pull


## main.c

```
#include "app_timer.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_TIM3_Init();

    app_timer_init();

    while (1)
    {
        app_timer_run();
    }
}
```


## Build
```
$ make -j$(nproc)
```


## Expected Output

```
    [ULTRA] 65.32 cm
    [ULTRA] 42.10 cm
```


## Architecture Rules

-   Only BSP calls HAL
-   DEV layer abstracts sensor behavior
-   APP layer contains logic only
-   No direct HAL access in APP


## Key Concepts

### 1. Input Capture

-   Rising edge → start time
-   Falling edge → end time

### 2. Overflow Handling

-   TIM3 is 16-bit → max 65535
-   Overflow must be handled manually

### 3. State Machine

    IDLE → WAIT_RISING → WAIT_FALLING → DONE

### 4. Non-blocking Design

-   No while polling
-   Interrupt-driven


## UNIT_TEST

Build with:

```
-DUNIT_TEST
```

-   HAL replaced with mock
-   Enables host-side testing


## Notes

-   ECHO must NOT be connected directly (5V → damage risk)
-   Use voltage divider
-   Typical range: 2cm \~ 400cm
