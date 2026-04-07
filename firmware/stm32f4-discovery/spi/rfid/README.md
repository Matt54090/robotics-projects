# STM32 RC522 SPI RFID Template

Layered architecture example for RC522 RFID using STM32 SPI.

## Target

-   MCU: STM32F407VG
-   Interface: SPI1
-   Chip: RC522 (MFRC522 compatible)
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc

## Repository Structure

app/ → Application logic\
bsp/ → HAL abstraction (SPI / GPIO)\
devices/ → RC522 device driver\
common/ → Register / protocol definitions

## Behavior

-   Initialize RC522 (reset + timer + RF ON)
-   Read version register
-   Detect card (REQA)
-   Read UID (ANTICOLL)
-   Print UID via UART

## main.c

    #include "app_spi.h"

    int main(void)
    {
        HAL_Init();
        SystemClock_Config();

        app_rc522_ctx_t ctx;

        app_spi_init(&ctx);

        while (1)
        {
            app_spi_run(&ctx);
            HAL_Delay(200);
        }
    }

## Build

    $ make -j$(nproc)

## Expected Output

    RC522 version: 0xB2
    ATQA: 04 00
    UID: XX XX XX XX

## Architecture Rules

-   Only BSP calls HAL
-   DEV layer handles RC522 protocol
-   APP layer prints and controls logic
-   No direct HAL access in APP

## Key Concepts

### 1. SPI Protocol

-   Address shifted (reg \<\< 1)
-   MSB = read/write flag

### 2. RC522 Flow

REQA → ANTICOLL → UID

### 3. FIFO

-   Commands push data into FIFO
-   Response read from FIFO

### 4. Timing

-   StartSend bit required
-   IRQ polling required

## UNIT_TEST

Build with:

    -DUNIT_TEST

-   HAL replaced with mock
-   Host testing possible with simulated SPI responses
