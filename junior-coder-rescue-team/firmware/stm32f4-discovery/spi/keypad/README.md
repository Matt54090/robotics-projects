# STM32 MCP23S17 SPI Keypad Template

Layered architecture example for keypad using MCP23S17 SPI GPIO
expander.

## Target

-   MCU: STM32F407VG
-   Interface: SPI1
-   Chip: MCP23S17 (SPI GPIO Expander)
-   Input: 4x4 Matrix Keypad
-   Toolchain: Makefile
-   Compiler: arm-none-eabi-gcc

## Repository Structure

app/ → Application logic\
bsp/ → HAL abstraction (SPI / GPIO)\
devices/ → Keypad driver (MCP23S17 based)\
common/ → Register / enum definitions

## Behavior

-   Initialize MCP23S17
-   Configure:
    -   GPA0\~3 → Output (Row)
    -   GPB0\~3 → Input (Column)
-   Enable internal pull-up (column)
-   Scan keypad matrix
-   Detect pressed key
-   Print key via UART

## main.c

    #include "app_keypad.h"

    int main(void)
    {
        HAL_Init();
        SystemClock_Config();

        app_keypad_ctx_t ctx;

        app_keypad_init(&ctx);

        while (1)
        {
            app_keypad_run(&ctx);
            HAL_Delay(50);
        }
    }

## Build

    $ make -j$(nproc)

## Expected Output

    KEY: 0
    KEY: 5
    KEY: 10

## Architecture Rules

-   Only BSP calls HAL
-   DEV layer handles MCP23S17 + keypad logic
-   APP layer controls flow and printing
-   No direct HAL access in APP

## Key Concepts

### 1. MCP23S17 SPI Protocol

    [ OPCODE ][ REGISTER ][ DATA ]

-   WRITE = 0x40
-   READ = 0x41

### 2. Keypad Matrix Scan

-   Row → Output
-   Column → Input (Pull-up)

Flow:

    Set one row LOW
    Read column
    Detect LOW → pressed

### 3. Active-Low Input

-   Default = HIGH (pull-up)
-   Pressed = LOW

### 4. Key Index Calculation

    key = row * 4 + col

### 5. Debounce

Mechanical switch bounce occurs:

    LOW → HIGH → LOW → HIGH

Solution:

-   Delay after row switching
-   Time-based debounce (\~50ms)

## UNIT_TEST

Build with:

    -DUNIT_TEST

-   HAL replaced with mock
-   SPI simulated
-   Logic test possible on host
