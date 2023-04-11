#!/bin/bash

ROOT_DIR=$(git rev-parse --show-toplevel)
export ENV SHELLCHECK_OPTS="--shell=bash --exclude=SC1090"

set -e

source "${ROOT_DIR}/scm/scripts/common/echo.sh"

cd "${ROOT_DIR}"
pwd

BASH_LISTS=$(find . \
	-not -path './.git/*' -a \
	-not -path './gentags.sh' -a \
	-not -path "${THIRD_PARTY_PATH}" -a \
	-not -path "${OUT_PATH}" -a \
	-not -path "${CGTOOLS_PATH}" \
	-name "*.sh"
)

for SCRIPT in ${BASH_LISTS}
do
	echo "Checking the ${SCRIPT}"
	shellcheck -x "${SCRIPT}"

	RET="$?"
	if [[ "${RET}" != "0" ]]
	then
		echo_func "[SCM ERR] Need to check the ${SCRIPT} file"
		exit 1
	fi
done

echo_func "[scm] Bash scripts CI test done!" 0
