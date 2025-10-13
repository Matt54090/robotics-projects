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
COMMON_DIR=${ROOT_DIR}/scm/scripts/common

VENV="${ROOT_DIR}/.env_for_jcrt"

source "${COMMON_DIR}/echo.sh"

cd "${ROOT_DIR}"
pwd

# if exist virtual envrionment for JCRT, remove it
if [[ -d "${VENV}" ]]
then
	rm -rf "${VENV}"
fi

# check the requirements.txt in the repository
req_files=$(find . \
	-type f \
	-not -path '*/.git/*' -a \
	-not -path "${BACKEND_VIRTUAL_ENV_PATH}" \
	-name 'requirements.txt')
if [[ "${req_files}" != "" ]]; then
	echo_func "[scm] Setup the virtual environment for the Python" 0
	python3 -m venv "${VENV}"
	source "${VENV}/bin/activate"
	pip install -U pip
	for req_file in ${req_files}
	do
		echo_func "[scm] Installing ${req_files}" 0
		pip install -r "${req_file}"
	done
fi

# check to exist the python files
py_files=$(find . \
	-type f \
	-not -path '*/.git/*' -a \
	-not -path "${BACKEND_VIRTUAL_ENV_PATH}" \
	-name '*.py')
if [[ "${py_files}" == "" ]]
then
	echo_func "[SCM ERR] Not exist the python files!" 1
	exit 0
fi

# check the coding style score
for py_file in ${py_files}
do
	echo_func "[scm] Start the checking coding style about the ${py_file}" 0

	# sort the import
	python3 -m isort "${py_file}"
	echo_func "[scm] Completed to check the \"isort\"" 0

	"${COMMON_DIR}/diff_check.sh"
	RET="$?"
	if [ "${RET}" -ne "0" ]
	then
		exit 1
	fi

	# coding style check
	python3 -m flake8 "${py_file}"

	RET="$?"
	if [ "${RET}" -ne "0" ]
	then
		exit 1
	fi
	echo_func "[scm] Completed to check the \"flake8\"" 0

	lint_result=$(pylint "${py_file}" 2>&1 | \
		grep "Your code" | \
		awk '{print $7}' | \
		awk -F '/' '{print $1}')
	if [[ "${lint_result}" != "10.00" ]]
	then
		echo_func "[SCM ERR] pylint result is ${lint_result}" 1
		pylint "${py_file}"
		exit 1
	fi
	echo_func "[scm] Completed to check the \"pylint\"" 0
	echo
done

rm -rf "${VENV}"

echo_func "[scm] Python CI test done!" 0
