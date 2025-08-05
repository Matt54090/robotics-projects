#!/bin/bash
# shellcheck source=/dev/null

check_result()
{
    if [ ! -e "${RESULT}" ]; then
        echo_func "[scm] Failed to get the target,," 1
        exit 1
    fi

    set +e
    CHECK=$(grep -iE "(err|warn)" < "${RESULT}")
    rm "${RESULT}"
    if [ "${CHECK}" != "" ]; then
        echo_func "[scm] occurred the issue error or warning when compile." 1
        exit 1
    fi
    set -e

    if [ -f "${1}" ]; then
        echo_func "[scm] Successfully the compile." 0
    else
        echo_func "[scm] Failed to get the target,," 1
        exit 1
    fi
}

check_build()
{
        make clean

        make 2>&1 | tee "${RESULT}"
        check_result "jcrt"

        make clean
}

set -e

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"
source "${ROOT_DIR}/scm/scripts/common/pigpio.sh"

MAKE="Makefile"
CMAKE="CMakeLists.txt"
RESULT="build.log"

#create_library

cd "${ROOT_DIR}" || exit 1
FILES=$(find . \
    -type f \
    -not -path "${BUILD_DIR}" -a \
    -not -path "${DUMMY_DIR}" \
    -name "*.c")
for FILE in ${FILES}
do
    REAL_PATH=$(realpath "${FILE}")
    DIR=$(dirname "${REAL_PATH}")
    cd "${DIR}" || exit 1

    if [ -e "${MAKE}" ]; then
        echo_func "[scm] Building ${FILE} using Makefile." 0
        check_build
    fi

    if [ -e "${CMAKE}" ]; then
        echo_func "[scm] Building ${FILE} using CMake." 0
        rm -rf build && mkdir build
        cd build || exit 1

        cmake ../
        check_build
        cd - && rm -rf build
    fi

    cd "${ROOT_DIR}" || exit 1
done

echo_func "[scm] build test complete for the C languages." 0
