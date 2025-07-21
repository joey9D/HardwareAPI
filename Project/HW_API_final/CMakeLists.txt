cmake_minimum_required(VERSION 3.22)


project(HW_API_final VERSION 0.1. LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "main")
set(CORE_LIB "HW_API/core")
set(GPIO_LIB "HW_API/gpio")



add_subdirectory(HW_API)
# needs to be added last
add_subdirectory(app)