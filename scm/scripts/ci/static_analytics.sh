#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

check_static_annalytics()
{
	# static anaytics using cppcheck
    cppcheck \
        --enable=all \
        --inconclusive \
        --std=c11 \
        --language=c \
        --platform=unix64 \
        --error-exitcode=1 \
        --verbose \
        --inline-suppr \
        --force \
        --suppress=missingIncludeSystem \
        .

	RET="$?"
	if [[ "${RET}" != "0" ]]
	then
		echo_func "[SCM ERR] Failed to pass the codes on the cppcheck" 1
		exit 1
	fi
}

check_static_annalytics_for_fw()
{
    cppcheck \
        --enable=warning,performance,portability \
        --check-level=exhaustive \
        --std=c11 \
        --error-exitcode=1 \
        --force \
        -Ihal_mock \
        -Iapp \
        -Idevices \
        -Ibsp \
        -Icommon \
        .

	RET="$?"
	if [[ "${RET}" != "0" ]]
	then
		echo_func "[SCM ERR] Failed to pass the codes for FW" 1
		exit 1
	fi
}

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

PI_DIR="${ROOT_DIR}/os/pi4"
GPIO_DIR="${PI_DIR}/gpio/c"
UART_DIR="${PI_DIR}/uart/c"
PWM_DIR="${PI_DIR}/pwm/c"

FIRMWARE_DIR="${ROOT_DIR}/firmware"
STM32_DIR="${FIRMWARE_DIR}/stm32f4-discovery"
FW_GPIO_DIR="${STM32_DIR}/gpio"

TEST_DIRS=(
    "${GPIO_DIR}"
    "${UART_DIR}"
    "${PWM_DIR}"
)

cd "${ROOT_DIR}" || exit 1
for DIR in "${TEST_DIRS[@]}"
do
    cd "${DIR}" || exit 1
    echo_func "[scm] Current Directory: ${DIR}" 0
    check_static_annalytics
    cd "${ROOT_DIR}" || exit 1
done

TEST_FW_DIRS=(
    "${FW_GPIO_DIR}"
)

cd "${ROOT_DIR}" || exit 1
for DIR in "${TEST_FW_DIRS[@]}"
do
    cd "${DIR}" || exit 1
    SUB_DIRS=$(find . -maxdepth 1 -type d ! -name .)
    for SUB_DIR in ${SUB_DIRS}
    do
        cd "${SUB_DIR}" || exit 1
        echo_func "[scm] Current Directory: ${DIR}/${SUB_DIR}" 0
        check_static_annalytics_for_fw
        cd .. || exit 1
    done
    cd "${ROOT_DIR}" || exit 1
done

echo_func "[scm] Static Analytics CI test done!" 0
