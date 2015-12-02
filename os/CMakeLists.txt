cmake_minimum_required(VERSION 2.8.8)
project(SUZUHA_OS)

set(SUZUHA_OS_SOURCES
    kernel/kernel.c
    lib/flags.c
    lib/lib_os.c
    lib/messages_f.c
    lib/mutex.c
    lib/null.c
    lib/stdio_.c
    lib/stdlib_.c
)

add_library(suzuha_os OBJECT "${SUZUHA_OS_SOURCES}")
set_target_properties(suzuha_os PROPERTIES OUTPUT_NAME _suzuha_os)
