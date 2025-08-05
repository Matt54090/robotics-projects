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

UNAME := $(shell uname -m)

CC = gcc
CFLAGS = -W -Wall -g -ggdb
TARGET = jcrt

LIBS = -lpthread -lpigpio -lserialport
INCLUDES = $(GIT_ROOT)/common/include

ifeq ($(UNAME), x86_64)
	LIBS += -L$(GIT_ROOT)/common/dummy/lib
	INCLUDES += -I$(GIT_ROOT)/common/dummy/include
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

all: $(TARGET)
	@printf $(BUILD_MSG)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) -I$(INCLUDES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	rm -rf $(OBJS) $(TARGET)
