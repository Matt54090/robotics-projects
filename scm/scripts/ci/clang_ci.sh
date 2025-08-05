#!/bin/bash

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
COMMON_DIR=${ROOT_DIR}/scm/scripts/common

source "${COMMON_DIR}/echo.sh"

cd "${ROOT_DIR}"
pwd

# check the clang-format using the .clang-format file
echo_func "[scm] clang-format checking" 0
FILES=$(find . \
    -type f \
    -not -path "${BUILD_DIR}" -a \
    -not -path "${DUMMY_DIR}" \
    \( -name "*.c" -o -name "*.h" \))
for FILE in ${FILES}
do
    echo "checking ${FILE},,"
    clang-format -i "${FILE}"
done

"${COMMON_DIR}/diff_check.sh"

RET="$?"
if [ "${RET}" -ne "0" ]
then
	exit 1
fi

echo_func "[scm] C language CI test done!" 0
