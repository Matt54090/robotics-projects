#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

check_result()
{
    if [ ! -e "${RESULT}" ]; then
        echo_func "[SCM ERR] Failed to get the target,," 1
        exit 1
    fi

    set +e
    CHECK=$(grep -iE "(err|warn)" < "${RESULT}")
    rm "${RESULT}"
    if [ "${CHECK}" != "" ]; then
        echo_func "[SCM ERR] occurred the issue error or warning when compile." 1
        exit 1
    fi
    set -e

    if [ -f "${1}" ]; then
        echo_func "[scm] Successfully the compile." 0
    else
        echo_func "[SCM ERR] Failed to get the target,," 1
        exit 1
    fi
}

check_build()
{
        make clean

        make 2>&1 | tee "${RESULT}"
        check_result "${1}"

        make clean
}

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"
source "${ROOT_DIR}/scm/scripts/common/pigpio.sh"

MAKE="Makefile"
CMAKE="CMakeLists.txt"
RESULT="build.log"

#create_library

cd "${ROOT_DIR}" || exit 1
FILES=$(find . \
    -type f \
    -not -path "${BUILD_DIR}" -a \
    -not -path "${DUMMY_DIR}" -a \
    -not -path "${FIRMWARE_DIR}" \
    -name "*.c")
for FILE in ${FILES}
do
    REAL_PATH=$(realpath "${FILE}")
    DIR=$(dirname "${REAL_PATH}")
    cd "${DIR}" || exit 1

    if [ -e "${MAKE}" ]; then
        echo_func "[scm] Building ${FILE} using Makefile." 0
        check_build "jcrt"
    fi

    if [ -e "${CMAKE}" ]; then
        echo_func "[scm] Building ${FILE} using CMake." 0
        rm -rf build && mkdir build
        cd build || exit 1

        cmake ../
        check_build "jcrt"
        cd - && rm -rf build
    fi

    cd "${ROOT_DIR}" || exit 1
done

cd "${ROOT_DIR}/firmware" || exit 1
FILES=$(find . -type f -name "Makefile")
for FILE in ${FILES}
do
    DIR=$(dirname "${FILE}")
    INTERFACE=$(basename "${DIR}")

    cd "${DIR}" || exit 1
    check_build "devices/dev_${INTERFACE}.o"
    cd - || exit 1
done

echo_func "[scm] build test complete for the C languages." 0
