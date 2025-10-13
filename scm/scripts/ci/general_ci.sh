#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# shellcheck source=/dev/null

set -e

PWD=$(pwd)
PROJECT_NAME=$(echo "${PWD}" | awk -F '/' '{print $2}')
git config --global --add safe.directory "/${PROJECT_NAME}"

ROOT_DIR=$(git rev-parse --show-toplevel)
COMMON_DIR=${ROOT_DIR}/scm/scripts/common

source "${COMMON_DIR}/echo.sh"

cd "${ROOT_DIR}"
pwd

git config --global http.sslVerify false

# print the basic informations
echo_func "[scm] OS version" 0
grep "VERSION=" < "/etc/os-release"

echo_func "[scm] Kernel version" 0
uname -a

echo_func "[scm] All the git branches" 0
git branch -a

# remove trailing lines
echo_func "[scm] Remove the trailing lines" 0
find . \
	-type f \
	-not -path './.git/*' -a \
	-not -path "${BUILD_DIR}" -a \
	-not -path "${DUMMY_DIR}" -a \
	-not -path "${BACKEND_VIRTUAL_ENV_PATH}" \
	! -name "${TAG_FILE}" \
	! -name "${CSCOPE_FILE}" \
	-exec sed -i '${/^$/d;}' {} \;

# trim whitespcae
echo_func "[scm] Trim whitespace" 0
find . \
	-type f \
	-not -path './.git/*' -a \
	-not -path "${BUILD_DIR}" -a \
	-not -path "${DUMMY_DIR}" -a \
	-not -path "${BACKEND_VIRTUAL_ENV_PATH}" \
	! -name "${TAG_FILE}" \
	! -name "${CSCOPE_FILE}" \
	-exec sed -i 's/[[:space:]]*$//' {} \;

"${COMMON_DIR}/diff_check.sh"

RET="$?"
if [ "${RET}" -ne "0" ]
then
	exit 1
fi

echo_func "[scm] General CI test done!" 0
