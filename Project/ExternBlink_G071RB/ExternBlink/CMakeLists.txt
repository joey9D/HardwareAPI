# 0.) Create code and CMake file
# 1.) mkdir build
# 2.) cd build
# 3.) cmake .. #configure cmake
# 4.) cmake --build .
# 5.) ./Executable -> here Blink_exec

cmake_minimum_required(VERSION 3.22)

project(ExternalBlink_G071RB VERSION 1.0 LANGUAGES C CXX ASM)

add_subdirectory(Core/Src)
add_subdirectory(STM32G0xx_HAL_Driver/Src)
add_subdirectory(gpio)


add_subdirectory(app)