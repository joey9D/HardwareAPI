add_library(${SYS_CLOCK_LIB} sys_clock.cpp)

target_include_directories(${SYS_CLOCK_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
