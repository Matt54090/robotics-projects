# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

CC = gcc
CFLAGS = -W -Wall
TARGET = test

GIT_ROOT = $(shell git rev-parse --show-toplevel)
INCLUDES = $(GIT_ROOT)/common/include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lpigpio -I$(INCLUDES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	rm -f $(OBJS) $(TARGET)
