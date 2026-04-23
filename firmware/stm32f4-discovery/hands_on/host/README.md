# UART Reader (STM32 Vehicle IoT)


## Overview

This script reads UART data from the STM32 Vehicle IoT project and
prints parsed events to the console.


## Features

-   Parses fixed 8-byte protocol frames
-   Supports:
    -   Door Open (Ultrasonic)
    -   IMU Alert (Acceleration)
    -   Low Battery Warning (ADC)
-   Verifies checksum
-   Ignores invalid frames


## Protocol Format

```
[0xAA](#type)[DATA(4B)][CHECKSUM][0x55]
```


### TYPE

-   0x01 → Door Open
-   0x02 → IMU Alert
-   0x03 → Battery Low


## Requirements

-   Python 3.x
-   pyserial

Install dependency:

```
$ python3 -m venv .env
$ source .env/bin/activate
(.env) $ pip install -U pip
(.env) $ pip install -r requirements.txt
```


## Usage

```
(.env) $ python uart_reader.py
```


## Configuration

Edit port and baud rate in the script:

```
uart = UartReader("/dev/ttyUSB0", 115200)
```


## Output Example

```
[DOOR] Open (dist=5cm)
[IMU] ALERT (accel=2.35g)
[BAT] LOW (3.10V)
```


## Notes

-   Ensure correct UART port and baud rate
-   Frame must start with 0xAA and end with 0x55
-   Invalid checksum packets are ignored
