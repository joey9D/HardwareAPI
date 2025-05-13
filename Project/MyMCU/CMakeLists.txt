cmake_minimum_required(VERSION 3.22)

find_program(CMAKE_ASM_COMPILER NAMES arm-none-eabi-gcc)
find_program(CMAKE_C_COMPILER NAMES arm-none-eabi-gcc)
find_program(CMAKE_CXX_COMPILER NAMES arm-none-eabi-g++)
find_program(CMAKE_LINKER NAMES arm-none-eabi-g++)
find_program(CMAKE_OBJCOPY NAMES arm-none-eabi-objcopy)
find_program(CMAKE_SIZE NAMES arm-none-eabi-size)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

####################################
# SET PROJECT NAME#
####################################
set(PROJECT_NAME My_MCU_Lib)
# set(PROJECT_NAME stm32c0)
# set(PROJECT_NAME stm32g0)
# set(PROJECT_NAME esp32_c6)

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
# CONFIGURE TARGET #
####################################
set(MCU_DRIVERS_LIBRARY mcu_drivers/stm32c0)
target_sources(cmsis PRIVATE ${MCU_DRIVERS_LIBRARY}/stm32c0/CMSIS/Device/ST/STM32C0xx/Source/startup_stm32c031xx.s)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -Wl,--gc-sections
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -T${CMAKE_CURRENT_SOURCE_DIR}/${MCU_DRIVERS_LIBRARY}/CMSIS/Device/ST/STM32C0xx/Source/linker/STM32C031C6TX_FLASHgit a.ld
)

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
