#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

export SHELLCHECK_OPTS="--shell=bash --exclude=SC1091"

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

cd "${ROOT_DIR}"
pwd

RESULT=$(find . \
	-not -path './.git/*' -a \
	-not -path './gentags.sh' -a \
	-not -path "${BUILD_DIR}" -a \
	-not -path "${DUMMY_DIR}" -a \
	-not -path "${BACKEND_VIRTUAL_ENV_PATH}" \
	-name "*.sh")
BASH_LISTS=$(echo "${RESULT}" | tr '\n' ' ')

for SCRIPT in ${BASH_LISTS}
do
	echo "Checking the ${SCRIPT}"
	shellcheck -x "${SCRIPT}"

	RET="$?"
	if [[ "${RET}" != "0" ]]
	then
		echo_func "[SCM ERR] Need to check the ${SCRIPT} file" 1
		exit 1
	fi
done

echo_func "[scm] Bash scripts CI test done!" 0
