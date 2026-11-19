# Prerequisites

We use the UART2 for the test.

First, add the values as below to the **/boot/firmware/config.txt** file.

```
dtparam=spi=off
enable_uart=1
dtoverlay=uart2,txd2_pin=0,rxd2_pin=1
```

Then, reboot the system.

Next, install the **raspi-gpio** tool and check the GPIO0/1 status as below.

```
$ sudo apt install raspi-gpio
$ raspi-gpio get 0
GPIO 0: level=1 alt=4 func=TXD2 pull=NONE
$ raspi-gpio get 1
GPIO 1: level=1 alt=4 func=RXD2 pull=UP
```

It must be set to ***alt=4*** and func is ***TXD2/RXD2***.

Finally, you can check the ttyAMA2 device for communication using UART2.

```
$ dmesg | grep AMA
fe201400.serial: ttyAMA2 at MMIO 0xfe201400 (irq = 39, base_baud = 0) is a PL011 rev3

$ ls -al /dev/ttyAMA2
crw-rw---- 1 root dialout 204, 66 Aug 15 21:12 /dev/ttyAMA2
```
