cmake_minimum_required(VERSION 2.8.8)
project(LIB_LOW_LEVEL_STM32F4)


file(GLOB_RECURSE LIB_LOW_LEVEL_STM32F4_SOURCES *.c)
add_library(lib_low_level OBJECT "${LIB_LOW_LEVEL_STM32F4_SOURCES}")
set_target_properties(lib_low_level PROPERTIES OUTPUT_NAME _low_level)
