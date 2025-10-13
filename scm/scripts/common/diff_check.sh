#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

DIFF=$(git diff)

if [ -z "${DIFF}" ]
then
	exit 0
fi

echo -e "\033[0;31m""[SCM ERR] Please correct the line below!""\033[0m"
git diff --exit-code
exit 1
