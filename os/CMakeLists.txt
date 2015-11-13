cmake_minimum_required(VERSION 2.8.8)
project(SUZUHA_OS)

file(GLOB_RECURSE SUZUHA_OS_SOURCES *.c)

add_library(suzuha_os OBJECT "${SUZUHA_OS_SOURCES}")
set_target_properties(suzuha_os PROPERTIES OUTPUT_NAME _suzuha_os)
