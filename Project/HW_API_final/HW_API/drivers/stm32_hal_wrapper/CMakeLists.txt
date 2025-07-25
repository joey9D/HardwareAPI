# STM32 HAL Provider - Downloads HAL drivers and makes them available
cmake_minimum_required(VERSION 3.16)

# Set default MCU family if not specified
if(NOT DEFINED STM32_MCU_FAMILY)
    set(STM32_MCU_FAMILY "STM32C0xx")
endif()

if(NOT DEFINED STM32_MCU_TYPE)
    set(STM32_MCU_TYPE "STM32C031xx")
endif()

message(STATUS "STM32 HAL Provider - MCU Family: ${STM32_MCU_FAMILY}, Type: ${STM32_MCU_TYPE}")

# Use FetchContent to download STM32 HAL if not provided externally
if(NOT DEFINED STM32_HAL_PATH)
    include(FetchContent)
    
    message(STATUS "Downloading STM32CubeC0 HAL from GitHub...")
    
    FetchContent_Declare(
        stm32cubec0
        GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeC0.git
        GIT_TAG v1.0.1
        GIT_SHALLOW TRUE
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/stm32cubec0
    )
    
    FetchContent_MakeAvailable(stm32cubec0)
    
    # Set HAL paths from downloaded content
    set(STM32_HAL_PATH "${CMAKE_CURRENT_BINARY_DIR}/stm32cubec0/Drivers/STM32C0xx_HAL_Driver")
    set(STM32_CMSIS_PATH "${CMAKE_CURRENT_BINARY_DIR}/stm32cubec0/Drivers/CMSIS")
    
    message(STATUS "STM32 HAL available at: ${STM32_HAL_PATH}")
    
    # Verify that the HAL was actually downloaded
    if(NOT EXISTS "${STM32_HAL_PATH}/Src/stm32c0xx_hal.c")
        message(FATAL_ERROR "STM32 HAL download failed. Expected file not found: ${STM32_HAL_PATH}/Src/stm32c0xx_hal.c")
    endif()
else()
    message(STATUS "Using external STM32 HAL from: ${STM32_HAL_PATH}")
    # Assume CMSIS is in standard location relative to HAL
    set(STM32_CMSIS_PATH "${STM32_HAL_PATH}/../CMSIS")
endif()

# Core HAL sources that your existing code needs
set(STM32_HAL_SOURCES
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_cortex.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_rcc.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_rcc_ex.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_pwr.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_flash.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_gpio.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_exti.c
    ${STM32_HAL_PATH}/Src/stm32c0xx_hal_dma.c
    # Add more HAL modules as your code needs them:
    # ${STM32_HAL_PATH}/Src/stm32c0xx_hal_uart.c
    # ${STM32_HAL_PATH}/Src/stm32c0xx_hal_spi.c
    # ${STM32_HAL_PATH}/Src/stm32c0xx_hal_tim.c
)

# CMSIS system file
set(STM32_SYSTEM_SOURCE
    ${STM32_CMSIS_PATH}/Device/ST/STM32C0xx/Source/Templates/system_stm32c0xx.c
)

# Bare metal support files
set(STM32_BARE_METAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32c031c6.c
)

# Create STM32 HAL library (just the drivers, no wrapper code)
add_library(stm32_hal_wrapper 
    ${STM32_HAL_SOURCES}
    ${STM32_SYSTEM_SOURCE}
    ${STM32_BARE_METAL_SOURCES}
)

# Make HAL includes available to your existing code
target_include_directories(stm32_hal_wrapper PUBLIC
    ${STM32_HAL_PATH}/Inc
    ${STM32_CMSIS_PATH}/Include
    ${STM32_CMSIS_PATH}/Device/ST/STM32C0xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}  # For our stm32c0xx_hal_conf.h
)

# Set compile definitions that your existing code expects
target_compile_definitions(stm32_hal_wrapper PUBLIC
    ${STM32_MCU_FAMILY}
    ${STM32_MCU_TYPE}
    USE_HAL_DRIVER
    HSE_VALUE=8000000
    HSI_VALUE=16000000
)

# Suppress HAL warnings
target_compile_options(stm32_hal_wrapper PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Wno-unused-parameter -Wno-unused-variable>
)
