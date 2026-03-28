# STM32 I2C LCD (HD44780 + PCF8574) Layered Template

Layered architecture example for I2C LCD using STM32.

Base STM32 project must be generated with CubeMX.


## Target

-   MCU: STM32F407VG
-   Interface: I2C (I2C1)
-   LCD: 1602 (HD44780 + PCF8574)
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc


## Repository Structure

    app/      → Application logic
    bsp/      → HAL abstraction (I2C)
    devices/  → LCD device layer
    common/   → LCD command / register definitions
    simple.ioc → CubeMX configuration


## Behavior

-   Initializes LCD (4-bit mode)
-   Controls backlight ON/OFF
-   Sets cursor position
-   Prints formatted strings to LCD


## Setup

1.  Open `simple.ioc` in CubeMX

2.  Configure:

    -   I2C1 → PB6 (SCL), PB9 (SDA)
    -   Mode → I2C
    -   Speed → 100kHz
    -   Toolchain → Makefile

3.  **Power (IMPORTANT)**

    - LCD VCC → 5V (NOT 3.3V)
    - LCD GND → GND

4.  **I2C Pull-up (required)**

    - SCL → 4.7kΩ → 3.3V
    - SDA → 4.7kΩ → 3.3V

5.  Generate Code

6.  Copy folders:

```
app/
bsp/
devices/
common/
```


## main.c

```
#include "app_lcd.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_I2C1_Init();

    app_lcd_init();

    while (1)
    {
        app_lcd_run();
    }
}
```


## Build

```
$ make -j$(nproc)
 ```


## Test

Expected LCD output:

```
    Hello, World!
    Hello, JCRT!
```


## Architecture Rules

-   Only BSP calls HAL (`HAL_I2C_*`)
-   Devices use BSP only
-   App uses Devices only
-   No business logic in main.c


## Notes

-   LCD must be powered with **5V**
-   I2C address: typically `0x27` or `0x3F`
-   Backlight control requires bit `0x08`
-   All I2C writes must include backlight bit


## UNIT_TEST

Build with:

```
-DUNIT_TEST
```

This replaces HAL I2C with mock functions for host testing.
