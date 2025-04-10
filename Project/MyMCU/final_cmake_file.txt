cmake_minimum_required(VERSION 3.15)
###############################################################
# NOTE:
#
# Depending on OS, varibale might ber case-sensitive.
# Make sure to use the correct case for the variables.
###############################################################
find_program(CMAKE_ASM_COMPILER NAMES arm-none-eabi-gcc)
find_program(CMAKE_C_COMPILER NAMES arm-none-eabi-gcc)
find_program(CMAKE_CXX_COMPILER NAMES arm-none-eabi-g++)
find_program(CMAKE_LINKER NAMES arm-none-eabi-g++)
find_program(CMAKE_OBJCOPY NAMES arm-none-eabi-objcopy)
find_program(CMAKE_SIZE NAMES arm-none-eabi-size)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

##############################################################
# VARIABLES
#
# Configure the variables to fit the used mcu board.
# read mcu board manuals for specific info
##############################################################
set(MCU_FAMILY STM32G0)
set(MCU_MODEL STM32G071RB)
set(CPU_ARCH cortex-m0plus)

set(FLOAT_ABI soft) # depending on mcu
set(FPU_TYPE none)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/mcu_drivers/${MCU_FAMIILY}/CMSIS/Device/ST/${MCU_FAMILY}xx/Source/linker/${MCU_MODEL}_FLASH.ld)

set(DEBUGGER JLINK) # JLINK, OPENOCD
set(JLINK_DEVICE ${MCU_MODEL})
set(OPENOCD_BOARD ${MCU_FAMILY})



##############################################################
# PROJECT NAME - must be mcu name
##############################################################
project(${MCU_FAMILY} C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


add_compile_options(
    -mcpu=${CPU_ARCH}
    -mfloat-abi=${FLOAT_ABI} # depending on mcu, if fpu is supported
    #-mfpu=fpv4-sp-d16
    -mthumb
    -ffunction-sections
    -fdata-sections
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
)

##############################################################
# BOARD and DRIVER LIBRARIES / PREPROCESSOR DEFINITIONS
# add the specific mcu board you want ot use/compile
# 
# supported boards:
#   - STM32G071xx
#   - STM32G0B1xx
#   - STM32C031xx
#   - ESP32-C6 DevKitC-1
#
# Add preprocessor defines/macros/definitions
# add_compile_definitions(
#     STM32G0xx
#     STM32G071xx
#     USE_HAL_DRIVER
#     HSE_VALUE=8000000U
#     HSI_VALUE=16000000U
#     VDD_VALUE=3300U
#     # Add other defines as needed
# )
##############################################################
add_compile_definitions(STM32G071xx)

add_subdirectory(mcu_drivers)
add_subdirectory(mcu_drivers/${MCU_FAMILY})

target_sources(cmsis PRIVATE
    mcu_drivers/${MCU_FAMILY}/startup_stm32g071xx.s
    # add files for other supported mcu boards
)

##############################################################
# FUNCTION LIBRARIES - add the libraries you want to use
##############################################################
add_subdirectory(core)
add_subdirectory(basic)
add_subdirectory(gpio)
add_subdirectory(timer)

##############################################################
# EXECUTABLE
##############################################################
add_executable(${CMAKE_PORJECT_NAME}
    app/main.cpp
)

##############################################################
# HARDWARE CONFIG
##############################################################
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=${CPU_ARCH}
    -mfloat-abi=${FLOAT_ABI}
    -mfpu=${FPU_TYPE}
    -Wl,--gc-sections
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
    -T${CMAKE_CURRENT_SOURCE_DIR}/periph/stm32f4/CMSIS/Device/ST/STM32F4xx/Source/linker/STM32F407VGTx_FLASH.ld
)

##############################################################
# EXECUTABLE
#
# Add the libraries you want to use.
##############################################################
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE_HEADER
    mcu_drivers
    #mcu_drivers/stm32g0
    # ... other mcu
    core
    basic
    gpio
    timer
    #spi
    #uart
)

##############################################################
# OUTPUT CONFIG 
##############################################################
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")

# convert .elf to .bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf "${CMAKE_PROJECT_NAME}.bin"
)

##############################################################
# FLASHING 
#
# Add targets for flashing, erasing, resetting and debugging
##############################################################
if(DEBUGGER STREQUAL "JLINK")
    set(JLINK_PARAMS -device ${JLINK_DEVICE} -if SWD)
    include(debug-probes/jlink.cmake)
elseif(DEBUGGER STREQUAL "OPENOCD")
    set(OPENOCD_SCRIPT board/${OPENOCD_BOARD}.cfg)
    include(debug-probes/openocd.cmake)
elseif(DEBUGGER STREQUAL "STLINK")
    set(STLINK_DEVICE ${MCU_MODEL})
    include(debug-probes/stlink.cmake)
elseif(DEBUGGER STREGUAL "ESPTOOL")
    set(ESPTOOL_DEVICE ${MCU_MODEL})
    include(debug-probes/esptool.cmake)
else
    message(FATAL_ERROR "Unsupported debugger: ${DEBUGGER}. Supported debuggers are JLINK, OPENOCD, and STLINK.")
endif()
