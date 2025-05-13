cmake_minimum_required(VERSION 3.22)

####################################
# SET PROJECT NAME#
####################################
set(PROJECT_NAME My_MCU_Lib)

project(
    ${PROJECT_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)

####################################
# SET LANGUAGE SETTINGS #
####################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

####################################
# ENABLE TESTING#
####################################
option(
    ENABLE_TESTING
    "Enable a Unit Testing Build" OFF # ON/OFF
)

####################################
# SET VARIABLES #
####################################
#set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME MainExe)
set(BASIC_LIBRARY basic)
set(CORE_LIBRARY core)
set(GPIO_LIBRARY gpio)
set(MCU_DRIVERS_LIBRARY mcu_drivers/stm32c0)
# set(I2C_LIBRARY i2c)
# set(SPI_LIBRARY spi)
# set(UART_LIBRARY uart)
set(APP_LIBRARY app)

####################################
# INCLUDE CMAKE MODULES #
####################################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(FetchContent)
include(Docs)

####################################
# LOGGING #
####################################
# FetchContent_Declare(
#     spdlog
#     GIT_REPOSITORY https://github.com/gabime/spdlog.git
#     GIT_TAG v1.15.2
#     GIT_SHALLOW TRUE
# )
# FetchContent_MakeAvailable(spdlog)

####################################
# CLI ARGUMENTS #
####################################
# FetchContent_Declare(
#     cxxopts
#     GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
#     GIT_TAG v3.2.0
#     GIT_SHALLOW TRUE
# )
# FetchContent_MakeAvailable(cxxopts)

####################################
# TESTING #
####################################
# if(ENABLE_TESTING)
#     FetchContent_Declare(
#         Catch2
#         GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#         GIT_TAG v3.8.1
#         GIT_SHALLOW TRUE
#     )
#     FetchContent_MakeAvailable(Catch2)
#     list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
# endif()

####################################
# ADD SUBDIR #
####################################
add_subdirectory(${CORE_LIBRARY})
add_subdirectory(${BASIC_LIBRARY})
add_subdirectory(${GPIO_LIBRARY})
add_subdirectory(${MCU_DRIVERS_LIBRARY})
add_subdirectory(${APP_LIBRARY})
# if(ENABLE_TESTING)
#     include(CTest)
#     enable_testing()
#     add_subdirectory(tests)
# endif()


####################################
# SELECT TARGET SRC #
####################################
#target_sources()
