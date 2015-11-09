cmake_minimum_required(VERSION 2.8.8)
project(SUZUHA_OS)

file(GLOB_RECURSE SUZUHA_OS_SOURCES *.c)
set(SUZUHA_OS_SOURCES "${SUZUHA_OS_SOURCES}" ../main.c)

add_library(suzuha_os STATIC "${SUZUHA_OS_SOURCES}")
set_target_properties(suzuha_os PROPERTIES OUTPUT_NAME _suzuha_os)

target_link_libraries(suzuha_os PUBLIC lib_low_level)
