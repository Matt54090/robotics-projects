#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

BACK_CR="\033[0m"
RED_CR="\033[0;31m"
GREEN_CR="\033[0;32m"

export BUILD_DIR="*/build/*"
export DUMMY_DIR="*/dummy/*"
export FIRMWARE_DIR="*/firmware/*"

export BACKEND_VIRTUAL_ENV_PATH="*/.env*/*"

export ETC_DIR="*/etc/*"

export TAG_FILE="tags"
export CSCOPE_FILE="cscope.*"

echo_func()
{
	if [[ $2 -eq 1 ]]
	then
		echo -e "${RED_CR}${1}${BACK_CR}"
	else
		echo -e "${GREEN_CR}${1}${BACK_CR}"
	fi
}
