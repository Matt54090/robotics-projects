#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

DUMMY_DIR="${ROOT_DIR}/common/dummy"
LIB_DIR="${DUMMY_DIR}/lib"
INCLUDE_DIR="${DUMMY_DIR}/include"

create_library()
{
    mkdir -p "${DUMMY_DIR}"
    mkdir -p "${LIB_DIR}"
    mkdir -p "${INCLUDE_DIR}"

    if [ -e "${LIB_DIR}/libpigpio.so" ]; then
        echo_func "[scm] The pigpio library already exists, skipping build." 0
        return
    fi

    git clone https://github.com/joan2937/pigpio.git
    cd pigpio || exit 1

    make

    mkdir temp
    make install DESTDIR="./temp"
    cp ./temp/usr/local/lib/libpigpio.so "${LIB_DIR}"
    cp ./temp/usr/local/include/pigpio.h "${INCLUDE_DIR}"

    cd - || exit 1
    rm -rf pigpio
}

create_library
