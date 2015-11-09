cmake_minimum_required(VERSION 2.8.8)
project(LIB_LOW_LEVEL_STM32F4)

file(GLOB_RECURSE LIB_LOW_LEVEL_STM32F4_SOURCES *.c)

add_library(lib_low_level STATIC "${LIB_LOW_LEVEL_STM32F4_SOURCES}")
set_target_properties(lib_low_level PROPERTIES OUTPUT_NAME _lowlevel)

target_compile_options(lib_low_level PUBLIC
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfloat-abi=softfp"
    "-mfpu=vfp"
    "-fsingle-precision-constant"
)
target_link_libraries(lib_low_level PUBLIC
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfloat-abi=softfp"
    "-mfpu=vfp"
    "-fsingle-precision-constant"

    "-T${CMAKE_SOURCE_DIR}/device/stm32f4/ldscript.ld"
)
