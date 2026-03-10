# STM32 GPIO Layered Template

This repository contains only the architecture layers.

You must generate the base STM32 project using CubeMX.


## Target

- MCU: STM32F407VG
- Toolchain: Makefile
- OS: Ubuntu 24.04
- Compiler: arm-none-eabi-gcc


## Repository Structure

```
app/        → Application logic
bsp/        → HAL abstraction layer
devices/    → Device drivers
common/     → Shared utilities
simple.ioc  → CubeMX configuration
```


## Step 1 – Generate Base Project

1. Open STM32CubeMX
2. Open `simple.ioc`
3. Verify:
   - PB12 → GPIO_Output
   - Label → GPIO_G_LED
   - Toolchain → Makefile
   - “Keep User Code when re-generating” enabled
4. Click **Generate Code**

This creates:

```
Core/
Drivers/
Makefile
```


## Step 2 – Copy Layers

Copy these folders into the generated project root:

```
app/
bsp/
devices/
common/
```

Final structure:

```
Core/
Drivers/
app/
bsp/
devices/
common/
Makefile
simple.ioc
```


## Step 3 – Update Makefile

Add to `C_SOURCES`:

```
C_SOURCES += \
app/app_main.c \
bsp/bsp_gpio.c \
devices/dev_led.c \
common/common.c
```

Add to `C_INCLUDES`:

```
C_INCLUDES += \
-Iapp \
-Ibsp \
-Idevices \
-Icommon
```


## Step 4 – Modify main.c

Add:

```
#include "app_main.h"
```

Inside main():

```
app_init();
```

Inside while loop:

```
app_run();
```

Only modify inside USER CODE sections.


## Step 5 – Build

```
$ make -j$(nproc)
```


## Step 6 – Flash

```
$ openocd \
    -f /usr/share/openocd/scripts/interface/stlink.cfg \
    -f /usr/share/openocd/scripts/target/stm32f4x.cfg \
    -c "program build/<project>.elf verify reset exit"
```

Replace `<project>` with your ELF name.


## Architecture Rules

- Only BSP calls HAL.
- Devices use BSP only.
- App uses Devices only.
- main.c contains no business logic.

This structure scales to larger embedded systems.

## Important

### Makefile

The provided Makefile is **CI-only**.

It is NOT used for flashing or running on hardware.

Firmware generation must be done via STM32CubeIDE + CubeMX.

---

### UNIT_TEST and Mocking

When building with:

-DUNIT_TEST

The project:

- Does NOT include real STM32 HAL
- Uses `hal_mock.h`
- Mocks GPIO and HAL functions

This allows CI compilation without STM32 HAL sources.

---

## Board Configuration

All pin mappings are defined in:

common/board_config.h

Example:
```
#define GPIO_G_LED_PORT GPIOB
#define GPIO_G_LED_PIN  GPIO_PIN_12
```

Change this file when switching boards.
