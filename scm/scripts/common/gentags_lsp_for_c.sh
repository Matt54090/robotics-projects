#!/bin/bash
# shellcheck source=/dev/null

ROOT_DIR=$(git rev-parse --show-toplevel)
source "${ROOT_DIR}/scm/scripts/common/echo.sh"

RESULT_JSON="compile_commands.json"
RESULT_TAG="tags"

if [ ! -f "Makefile" ]; then
    echo_func "[SCM ERR] No Makefile found in the current directory." 1
    exit 1
fi

make clean

echo_func "[scm] exporting the system include path..." 0
readarray -t INCLUDE_ARRAY < <(
  gcc -E -x c - -v < /dev/null 2>&1 |
  awk '/#include <...> search starts here:/, /End of search list./ {
    if ($1 != "#include") print "-I" $1
  }' | grep -v '^$'
)

SYS_INCLUDES="${INCLUDE_ARRAY[*]}"

export CFLAGS="${CFLAGS} ${SYS_INCLUDES}"

rm -f tags compile_commands.json

echo_func "[scm] create ctags,," 0
ctags -R \
  --languages=C,Python,Asm \
  --langmap=C:.c.h \
  --langmap=Python:.py \
  --langmap=Asm:.s \
  --extras=+q \
  --fields=+l \
  --links=no \
  --exclude=.git \
  --exclude=build \
  -f tags \
  "${ROOT_DIR}"

echo_func "[scm] check the build using bear" 0
bear -- make CC=gcc

mv "${RESULT_JSON}" "${RESULT_TAG}" "${ROOT_DIR}"
echo_func "[scm] Created the compile_commands.json w/ tags in ${ROOT_DIR}" 0
