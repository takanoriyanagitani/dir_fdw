cmake_minimum_required(VERSION 3.5)

project(dir_fdw)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g -coverage")

add_compile_options(
  -mavx2
  -ftree-vectorize
  -Wall
  -Werror
)

find_package(PostgreSQL REQUIRED COMPONENTS Server)

add_library(dir_fdw SHARED dir_fdw.c)
set_property(TARGET dir_fdw PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET dir_fdw PROPERTY PREFIX "")
target_include_directories(dir_fdw PRIVATE
  ${PostgreSQL_TYPE_INCLUDE_DIR}
)
