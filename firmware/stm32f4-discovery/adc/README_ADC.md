# STM32 ADC Layered Template

Layered architecture example for ADC input using polling mode on STM32.

Base STM32 project must be generated with CubeMX.


## Target

* MCU: STM32F407VG
* Interface: ADC (ADC1)
* Channel: IN8 (PB0)
* Toolchain: Makefile
* Compiler: arm-none-eabi-gcc


## Repository Structure

```
app/ → Application logic
bsp/ → HAL abstraction (ADC)
devices/ → ADC device layer
common/ → Config and definitions
simple.ioc → CubeMX configuration
```


## Behavior

* Reads ADC value from potentiometer (PB0)
* Converts raw value to voltage
* Prints voltage via UART


## Setup

1. Open simple.ioc in CubeMX
2. Configure:

   * ADC1 → Enable
   * Channel → IN8 (PB0)
   * Resolution → 12bit
   * Continuous Mode → Disabled
   * External Trigger → Software Start
   * PB0 → Analog mode / No pull
   * Toolchain → Makefile

3. Generate Code

Copy these folders into the project root:

```
app/
bsp/
devices/
common/
```


## main.c

```
#include "app_adc.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_ADC1_Init();
    MX_USART2_UART_Init();

    app_adc_init();

    while (1)
    {
        app_adc_run();
    }
}
```


## Build

```
make -j$(nproc)
```


## IMPORTANT (float printf)

If voltage is not printed correctly, you MUST enable float support.

Add this to Makefile:

```
LDFLAGS += -u _printf_float
```

or

```
LDLIBS += -u _printf_float
```

Then rebuild:

```
make clean
make
```


## Expected Output

[ADC] voltage = 1.23 V
[ADC] voltage = 2.45 V


## Alternative (recommended)

```
uint32_t raw;
dev_adc_read_raw(&raw);

uint32_t mv = (raw * 3300) / 4095;
dev_printf("%lu mV\r\n", mv);
```


## Architecture Rules

* Only BSP calls HAL
* Devices use BSP only
* App uses Devices only
* No business logic in main.c


## UNIT_TEST

Build with:

```
-DUNIT_TEST
```

This replaces STM32 HAL with mock implementations for native testing.


## Summary

```
ADC pin: PB0 (ADC1_IN8)
Structure: HAL → BSP → DEV → APP
Float printf requires -u _printf_float
```
