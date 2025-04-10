cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME My_Lib)

project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_NAME MainExe)
#set(LIBRARY_NAME Library)
set(BASIC_LIBRARY_NAME basic)
set(GPIO_LIBRARY_NAME gpio)
set(APP_LIBRARY_NAME app)

add_subdirectory(${BASIC_LIBRARY_NAME})
add_subdirectory(${GPIO_LIBRARY_NAME})
add_subdirectory(${APP_LIBRARY_NAME})
