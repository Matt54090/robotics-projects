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

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

PI_DIR="${ROOT_DIR}/os/pi4"
GPIO_DIR="${PI_DIR}/gpio/c"
UART_DIR="${PI_DIR}/uart/c"
PWM_DIR="${PI_DIR}/pwm/c"

TEST_DIRS=(
    "${GPIO_DIR}"
    "${UART_DIR}"
    "${PWM_DIR}"
)

cd "${ROOT_DIR}" || exit 1
for DIR in "${TEST_DIRS[@]}"
do
    cd "${DIR}" || exit 1
    check_static_annalytics
    cd "${ROOT_DIR}" || exit 1
done

echo_func "[scm] Static Analytics CI test done!" 0
