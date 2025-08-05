# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

RED := \033[0;31m
GREEN := \033[0;32m
RESET := \033[0m

GIT_ROOT = $(shell git rev-parse --show-toplevel)
DUMMY_ROOT = $(GIT_ROOT)/common/dummy

CC = gcc
CFLAGS = -W -Wall -g -ggdb
TARGET = jcrt

LIBS = -lpthread -lpigpio -lserialport
INCLUDES = $(GIT_ROOT)/common/include

UNAME := $(shell uname -m)
ifeq ($(UNAME), x86_64)
	LIBS += -L$(DUMMY_ROOT)/lib
	INCLUDES += -I$(DUMMY_ROOT)/include

	PIGPIO_LIB = $(DUMMY_ROOT)/lib/libpigpio.so
endif

BUILD_MODE ?= debug
ifeq ($(BUILD_MODE), debug)
	CFLAGS += -DDEBUG
	BUILD_MSG := "$(GREEN)[JCRT] Complete to build w/ DEBUG mode!$(RESET)\n"
else
	BUILD_MSG := "$(GREEN)[JCRT] Complete to build w/ RELEASE mode.$(RESET)\n"
endif

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(PIGPIO_LIB) $(TARGET)
	@printf $(BUILD_MSG)

$(PIGPIO_LIB):
	@printf "$(RED)[JCRT] Try to build the pigpio library!$(RESET)\n"
	@bash $(GIT_ROOT)/scm/scripts/common/pigpio.sh

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) -I$(INCLUDES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	rm -rf $(OBJS) $(TARGET)
