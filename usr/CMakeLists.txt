cmake_minimum_required(VERSION 2.8.8)
project(AERIS_USR_TARGETS)


set(TARGETS tests)

foreach(program ${TARGETS})
    add_executable(${program} ${program}.c)
    target_link_libraries(${program} lib_low_level suzuha_os lib_usr)
    set_target_properties(${program} PROPERTIES OUTPUT_NAME ${CMAKE_BINARY_DIR}/${program}.elf)

    add_custom_command(TARGET ${program}
        POST_BUILD
        COMMENT "Translating ${CMAKE_BINARY_DIR}/${program}.bin"
        COMMAND ${ARM-OBJCOPY} -O binary "${CMAKE_BINARY_DIR}/${program}.elf" "${CMAKE_BINARY_DIR}/${program}.bin"
    )
endforeach()
