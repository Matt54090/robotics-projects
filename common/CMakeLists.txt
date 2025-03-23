# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

cmake_minimum_required(VERSION 3.10)

project(
  jcrt
  VERSION 0.0.1
  LANGUAGES C)

# set the GIT_DIR
find_package(Git)
if(Git_FOUND)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" rev-parse --show-toplevel
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_DIR
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
  set(GIT_DIR "../")
endif()

# include the common source files
include_directories("${GIT_DIR}/common/include")

# set the source files
file(GLOB JCRT_SRC *.c)

# make exe file
add_executable(${PROJECT_NAME} ${JCRT_SRC})

# set the compile option for the target
target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -g -ggdb)

# link the external library
target_link_libraries(${PROJECT_NAME} pigpio)
