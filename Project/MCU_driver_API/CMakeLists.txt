cmake_minimum_required(VERSION 3.22)

# find_program(CMAKE_ASM_COMPILER NAMES arm-none-eabi-gcc)
# find_program(CMAKE_C_COMPILER NAMES arm-none-eabi-gcc)
# find_program(CMAKE_CXX_COMPILER NAMES arm-none-eabi-g++)
# find_program(CMAKE_LINKER NAMES arm-none-eabi-g++)
# find_program(CMAKE_OBJCOPY NAMES arm-none-eabi-objcopy)
# find_program(CMAKE_SIZE NAMES arm-none-eabi-size)
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# -----------------------------------------
# SET PROJECT NAME#
# -----------------------------------------
# set(PROJECT_NAME My_MCU_Lib) # Project name needs to be mcu specific
set(PROJECT_NAME stm32c0)
# set(PROJECT_NAME stm32g0)
# set(PROJECT_NAME esp32_c6)

project(
    ${PROJECT_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)

# -----------------------------------------
# SET LANGUAGE SETTINGS #
# -----------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------
# ENABLE TESTING#
# -----------------------------------------
option(
    ENABLE_TESTING
    "Enable a Unit Testing Build" OFF # ON/OFF
)


# -----------------------------------------
# INCLUDE CMAKE MODULES #
# -----------------------------------------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(FetchContent)
include(Docs)

# -----------------------------------------
# COMPILE OPTIONS #
# -----------------------------------------
# MCU being used #
add_compile_definitions(STM32C031xx)

# RTOS #
# add_compile_definitions(FREERTOS_USED)

# add_compile_options(
#     -mcpu=cortex-m0plus
#     #    -mfloat-abi=hard
#     #    -mfpu=fpv4-sp-d16
#     -mthumb
#     -ffunction-sections
#     -fdata-sections
#     $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
#     $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
#     $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
#     $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
#     )


# -----------------------------------------
# TESTING #
# -----------------------------------------
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


# -----------------------------------------
# INCLUDE SUBDIRECTORIES/LIBS #
# -----------------------------------------
#set(LIBRARY_NAME Library)

# if(ENABLE_TESTING)
#     include(CTest)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# HW_API #
set(HW_API_LIBRARY HW_API)
add_subdirectory(HW_API)
# libs as variables
# set(BASIC_LIB ${HW_API_LIBRARY}/basic)
set(CORE_LIB ${HW_API_LIBRARY}/core)
set(DRIVERS_LIB ${HW_API_LIBRARY}/drivers)
set(GPIO_LIB ${HW_API_LIBRARY}/gpio)
# set(I2C_LIB ${HW_API_LIBRARY}/i2c)
# set(SPI_LIB ${HW_API_LIBRARY}/spi)
set(STM32_LIB ${HW_API_LIBRARY}/stm32)
set(SYS_CLOCK_LIB ${HW_API_LIBRARY}/sys_clock)
# set(UART_LIB ${HW_API_LIBRARY}/uart)

# MAIN EXECUTABLE #
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(APP_LIBRARY app)
add_subdirectory(${APP_LIBRARY})


# Add targets for flashing, erasing, resetting and debugging
# set(JLINK_PARAMS -device STM32C031C6 -if SWD)
# include(debug_probes/jlink.cmake)
include(debug_probes/st-link.cmake)
