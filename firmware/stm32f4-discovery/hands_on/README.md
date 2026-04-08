# STM32 Vehicle IoT Hands-On Project


## Overview

This project demonstrates a layered embedded system architecture using
STM32F4. It integrates multiple peripherals (SPI, I2C, UART, PWM, TIMER,
ADC) to build a simple vehicle IoT system.


## Target

-   MCU: STM32F407VG
-   Toolchain: arm-none-eabi-gcc
-   Build: Makefile
-   Architecture: app / devices / bsp


## Architecture

app/ → State machine, event handling\
devices/ → Sensor/actuator abstraction\
bsp/ → HAL wrapper\
common/ → shared definitions


### Rules

-   APP → devices only
-   devices → bsp only
-   bsp → HAL only


## Features


### 1. Idle State

-   Green LED ON
-   LCD shows battery voltage


### 2. Door Control (Keypad)

-   4x4 keypad via MCP23S17 (SPI)
-   Password: 1234
-   Servo opens door
-   Yellow LED blinks
-   UART protocol sent


### 3. Intrusion Detection (Ultrasonic)

-   Distance \< 10cm
-   Red LED blink
-   LCD alert
-   UART event


### 4. Vehicle Alert (IMU)

-   Acceleration \> threshold
-   Red LED blink
-   UART alert


## Key Components


### Keypad (SPI)

-   MCP23S17 GPIO expander
-   Matrix scan (row/col)


### Ultrasonic (Timer Input Capture)

-   Trigger: GPIO
-   Echo: Timer capture


### IMU (I2C)

-   MPU6050
-   Acceleration magnitude


### ADC

-   Battery voltage measurement


## UART Protocol

Frame: \[0xAA\]\[TYPE\]\[DATA(4B)\]\[CHECKSUM\]\[0x55\]

TYPE: - 0x01 → Door Open - 0x02 → Intrusion - 0x03 → IMU Alert


## Build

```
$ make -j\$(nproc)
```


## Notes

-   Blocking code acceptable for PoC
-   Tick-based debounce recommended for keypad
-   No HAL usage in app layer
-   Global logger allowed for simplicity


## Summary

This project demonstrates: - Layered embedded design - Peripheral
integration - Event-driven control - Basic IoT communication
