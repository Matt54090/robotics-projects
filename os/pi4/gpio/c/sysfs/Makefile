# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

CC = gcc
CFLAGS = -W -Wall
TARGET = test

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
