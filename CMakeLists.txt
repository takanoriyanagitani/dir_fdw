cmake_minimum_required(VERSION 3.0)

project(dir_fdw)

add_compile_options(
  -mavx2
  -ftree-vectorize
  -Wall
  -Werror
)

add_library(dir_fdw SHARED dir_fdw.c)
set_property(TARGET dir_fdw PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET dir_fdw PROPERTY PREFIX "")
target_include_directories(dir_fdw PRIVATE
  /usr/include/postgresql/12/server
)
