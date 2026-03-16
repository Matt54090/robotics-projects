# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

CC      := arm-none-eabi-gcc
CFLAGS  := -mcpu=cortex-m4 \
           -mthumb \
           -mfpu=fpv4-sp-d16 \
           -mfloat-abi=hard \
           -std=c11 \
           -Wall -Wextra \
           -ffreestanding \
           -Icommon \
           -Ibsp \
           -Idevices \
           -Iapp \
		   -DUNIT_TEST

SRC := $(wildcard app/*.c) \
       $(wildcard bsp/*.c) \
       $(wildcard common/*.c) \
       $(wildcard devices/*.c)

OBJ := $(SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f app/*.o bsp/*.o common/*.o devices/*.o
