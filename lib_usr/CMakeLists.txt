cmake_minimum_required(VERSION 2.8.8)
project(AERIS_LIB_USR)

set(AERIS_LIB_USR_SOURCES
    aeris_robot/aeris_robot.c
    aeris_robot/aeris_util.c
    aeris_robot/line_sensor.c
    lsm9ds0.c
    math.c
)

add_library(lib_usr STATIC "${AERIS_LIB_USR_SOURCES}")
set_target_properties(lib_usr PROPERTIES OUTPUT_NAME _usr)

target_link_libraries(lib_low_level)
