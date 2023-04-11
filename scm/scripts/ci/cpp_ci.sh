#!/bin/bash

ROOT_DIR=$(git rev-parse --show-toplevel)

set -e

source "${ROOT_DIR}/scm/scripts/common/echo.sh"

cd "${ROOT_DIR}"
pwd

# check to use the cpplint
echo_func "[scm] cpplint checking" 0

FILES=$(find . \
	-type f \
	-not -path "${THIRD_PARTY_PATH}" -a \
	-not -path "${OUT_PATH}" -a \
	-not -path "${CGTOOLS_PATH}" \
	\( -name "*.cpp" -o -name "*.h" \)
)

for file in ${FILES}
do
	cpplint "${file}"

	RET="$?"
	if [ "${RET}" -ne "0" ]
	then
		echo_func "[SCM ERR] Need to check the ${file}." 1
		exit 1
	fi
done

echo_func "[scm] C++ language CI test done!" 0
