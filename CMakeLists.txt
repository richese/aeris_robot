cmake_minimum_required(VERSION 2.8.8)

include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR stm32f4)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)

# set compiler
find_program(ARM-CC arm-none-eabi-gcc)
find_program(ARM-CXX arm-none-eabi-g++)
find_program(ARM-OBJCOPY arm-none-eabi-objcopy)
find_program(ARM-OBJDUMP arm-none-eabi-objdump)

CMAKE_FORCE_C_COMPILER("${ARM-CC}" GNU)
CMAKE_FORCE_CXX_COMPILER("${ARM-CXX}" GNU)

project(AERIS-ROBOT)

add_compile_options(
    "-Wall"
    "-Wextra"
    "-Wshadow"
    "-Wpointer-arith"
    "-Wcast-qual"
    "-Wcast-align"
    "-pedantic"

    "-fdata-sections"
    "-ffunction-sections"

    "-std=c99"

    "-O2"
    "-Os"
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfloat-abi=softfp"
    "-mfpu=vfp"
    "-fsingle-precision-constant"
)
link_libraries(
    "-mthumb"
    "-Wl,--gc-sections"
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfloat-abi=softfp"
    "-mfpu=vfp"
    "-fsingle-precision-constant"

    "-T${CMAKE_SOURCE_DIR}/device/stm32f4/ldscript.ld"
)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(device)
add_subdirectory(os)
add_subdirectory(lib_usr)
add_subdirectory(usr)
