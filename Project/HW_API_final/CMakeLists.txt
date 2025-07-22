cmake_minimum_required(VERSION 3.22)


project(HW_API_final VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "main")
set(CORE_LIBNAME "core")
set(GPIO_LIBNAME "gpio")
set(SPI_LIBNAME "spi")


add_subdirectory(HW_API)

# needs to be added last
add_subdirectory(app)
