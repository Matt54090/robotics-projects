#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

if [[ "$#" == "0" ]]
then
    echo_func "[JCRT ERR] need to folder name for creating." 1
    exit 1
fi

cd "${ROOT_DIR}/firmware/stm32f4-discovery" || exit 1
if [[ -d "${1}" ]]
then
    echo_func "[JCRT ERR] The ${1} folder already exists." 1
    exit 1
fi

mkdir "${1}" && cd "${1}" || exit 1
idx=0
DIRS=("app" "bsp" "common" "devices")
FILES=( "app" "bsp" "common" "dev" )
for DIR in "${DIRS[@]}"
do
    mkdir "${DIR}"

    touch "${DIR}/${FILES[idx]}_${1}.c"
    touch "${DIR}/${FILES[idx]}_${1}.h"
    ((idx++))
done
cd - || exit 1

tree "${1}"

echo_func "[jcrt] The ${1} discovery tree is created!" 0
