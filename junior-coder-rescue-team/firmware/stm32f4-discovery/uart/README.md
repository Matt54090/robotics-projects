# STM32 UART TX Layered Template

Layered architecture example for UART TX using interrupt mode on STM32.

Base STM32 project must be generated with CubeMX.

## Target

* MCU: STM32F407VG
* Interface: UART (USART2)
* Toolchain: Makefile
* Compiler: arm-none-eabi-gcc

## Repository Structure

```
app/ → Application logic
bsp/ → HAL abstraction (UART, Time)
devices/ → UART device layer
common/ → Enums and config
simple.ioc → CubeMX configuration
```

## Behavior

* Sends `[STM] alive N` every 1 second
* Uses interrupt-based TX (`HAL_UART_Transmit_IT`)
* Busy polling prevents TX overlap

## Setup

1. Open `simple.ioc` in CubeMX
2. Configure:

   * USART2 → Asynchronous mode
   * PA2 (TX), PA3 (RX)
   * Baudrate → 115200
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

Inside USER CODE sections:

```
#include "app_uart.h"

app_uart_ctx_t uart_ctx;

app_uart_init(&uart_ctx);

while (1)
{
    app_uart_run(&uart_ctx);
}
```

## Build

```
$ make -j$(nproc)
```

## Test

```
$ minicom -D /dev/ttyUSB0 -b 115200
```

Expected output:

```
[STM] alive 0
[STM] alive 1
...
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
