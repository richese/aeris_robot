cmake_minimum_required(VERSION 2.8.8)
project(AERIS_USR_TARGETS)


set(TARGETS template tests line_follower)

foreach(program ${TARGETS})
    set(TARGET_HEADER "usr/${program}.h")
    set(TARGET_SUZUHA_MAIN "${CMAKE_BINARY_DIR}/main_${program}.c")
    configure_file("${CMAKE_SOURCE_DIR}/main.c.in" "${TARGET_SUZUHA_MAIN}")

    add_executable(${program}
        ${program}.c ${TARGET_SUZUHA_MAIN}
        $<TARGET_OBJECTS:lib_low_level>
        $<TARGET_OBJECTS:suzuha_os>
        $<TARGET_OBJECTS:lib_usr>
    )
    set_target_properties(${program} PROPERTIES OUTPUT_NAME ${CMAKE_BINARY_DIR}/${program}.elf)
    add_custom_command(TARGET ${program}
        POST_BUILD
        COMMENT "Translating ${CMAKE_BINARY_DIR}/${program}.bin"
        COMMAND ${ARM-OBJCOPY} -O binary "${CMAKE_BINARY_DIR}/${program}.elf" "${CMAKE_BINARY_DIR}/${program}.bin"
    )
endforeach()
