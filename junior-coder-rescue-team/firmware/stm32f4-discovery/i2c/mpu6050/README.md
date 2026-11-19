# STM32 I2C MPU6050 Layered Template

Layered architecture example for MPU6050 using I2C on STM32.

Base STM32 project must be generated with CubeMX.

## Target

* MCU: STM32F407VG
* Interface: I2C (I2C1)
* Sensor: MPU6050
* Toolchain: Makefile
* Compiler: arm-none-eabi-gcc

## Repository Structure

```
app/ → Application logic
bsp/ → HAL abstraction (I2C)
devices/ → MPU6050 device layer
common/ → Register definitions
simple.ioc → CubeMX configuration
```

## Behavior

* Initializes MPU6050 (wake-up)
* Reads WHO_AM_I register
* Periodically reads accel/gyro data
* Outputs sensor data via UART

## Setup

1. Open `simple.ioc` in CubeMX

2. Configure:

   * I2C1 → PB6 (SCL), PB9 (SDA)
   * Mode → I2C
   * Speed → 100kHz
   * Toolchain → Makefile

3. **Add pull-up resistors (required)**

```
SCL → 4.7kΩ → 3.3V
SDA → 4.7kΩ → 3.3V
```

4. Generate Code

5. Copy folders:

```
app/
bsp/
devices/
common/
```

## main.c

```
#include "app_mpu6050.h"

app_mpu6050_ctx_t mpu_ctx;

app_mpu6050_init(&mpu_ctx);

while (1)
{
    app_mpu6050_run(&mpu_ctx);
}
```

## Build

```
$ make -j$(nproc)
```

## Test

In Host,

```
$ minicom -D /dev/ttyUSB0 -b 115200 -c on
```

Expected output:

```
id: 0x68
acc: xxxx xxxx xxxx / gyro: xxxx xxxx xxxx
```

## Architecture Rules

* Only BSP calls HAL (`HAL_I2C_*`)
* Devices use BSP only
* App uses Devices only
* No business logic in main.c

## Notes

* I2C requires external pull-up resistors
* MPU6050 default address: `0x68`
* Uses HAL memory read/write (`HAL_I2C_Mem_Read/Write`)

## UNIT_TEST

Build with:

```
-DUNIT_TEST
```

This replaces HAL I2C with mock functions for host testing.
