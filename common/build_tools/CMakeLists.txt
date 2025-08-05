# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

# set the build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      debug
      CACHE STRING "Build type" FORCE)
endif()

# set the project name
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
  set(GIT_DIR "../../")
endif()

# include the common source files
include_directories("${GIT_DIR}/common/include")

# set the source files
file(GLOB JCRT_SRC *.c)

# make exe file
add_executable(${PROJECT_NAME} ${JCRT_SRC})

# set the target properties
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  target_include_directories(
      ${PROJECT_NAME}
      PRIVATE
      ${GIT_DIR}/common/dummy/include
  )

  target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${GIT_DIR}/common/dummy/lib
  )
endif()

# set the compile option for the target
set(COMFILE_OPTIONS -W -Wall -g -ggdb)
if(CMAKE_BUILD_TYPE STREQUAL "debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
  list(APPEND COMFILE_OPTIONS -DDEBUG)
endif()
target_compile_options(${PROJECT_NAME} PRIVATE ${COMFILE_OPTIONS})

# link the external library
target_link_libraries(${PROJECT_NAME} pthread pigpio serialport)
