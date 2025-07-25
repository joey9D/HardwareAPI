# HW_API - Hardware Abstraction Layer
cmake_minimum_required(VERSION 3.22)

# Project kann als eigenständiges Projekt oder als Subdirectory verwendet werden
if(NOT CMAKE_PROJECT_NAME)
    project(HW_API VERSION 1.0.0 LANGUAGES C CXX)
endif()

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection - Enhanced for standalone operation
if(NOT DEFINED TARGET_PLATFORM)
    # Check command line definition first
    if(DEFINED CACHE{TARGET_PLATFORM})
        set(TARGET_PLATFORM ${TARGET_PLATFORM})
    # ESP-IDF detection
    elseif(ESP_PLATFORM OR DEFINED ENV{IDF_PATH} OR DEFINED IDF_PATH)
        set(TARGET_PLATFORM "ESP32")
        add_definitions(-DESP32_PLATFORM)
    # STM32 detection (toolchain or HAL path)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Generic" OR 
           DEFINED STM32_FAMILY OR 
           DEFINED STM32_HAL_PATH OR
           CMAKE_C_COMPILER MATCHES "arm-none-eabi")
        set(TARGET_PLATFORM "STM32")
        add_definitions(-DSTM32_PLATFORM)
    else()
        set(TARGET_PLATFORM "TEST")
        add_definitions(-DTEST_PLATFORM)
    endif()
endif()

message(STATUS "HW_API Target Platform: ${TARGET_PLATFORM}")

# Platform-specific HAL configuration
if(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP-IDF path detection and setup
    if(NOT DEFINED IDF_PATH)
        if(DEFINED ENV{IDF_PATH})
            set(IDF_PATH $ENV{IDF_PATH})
        else()
            message(WARNING "ESP-IDF path not found. Set IDF_PATH environment variable or use -DIDF_PATH=...")
        endif()
    endif()
    message(STATUS "ESP-IDF Path: ${IDF_PATH}")
    
elseif(TARGET_PLATFORM STREQUAL "STM32")
    # STM32 HAL path detection and setup
    # Only check environment if not already set by toolchain or command line
    if(NOT DEFINED STM32_HAL_PATH AND DEFINED ENV{STM32_HAL_PATH})
        set(STM32_HAL_PATH $ENV{STM32_HAL_PATH})
    endif()
    
    # If still not defined, let the HAL wrapper handle the download
    if(NOT DEFINED STM32_HAL_PATH)
        message(WARNING "STM32 HAL path not found. Set STM32_HAL_PATH environment variable or use -DSTM32_HAL_PATH=...")
    endif()
    message(STATUS "STM32 HAL Path: ${STM32_HAL_PATH}")
    
    # STM32 MCU family detection
    if(NOT DEFINED STM32_MCU_FAMILY)
        set(STM32_MCU_FAMILY "STM32C0xx" CACHE STRING "STM32 MCU Family (e.g., STM32C0xx, STM32F4xx)")
    endif()
    message(STATUS "STM32 MCU Family: ${STM32_MCU_FAMILY}")
endif()

# Global include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers
    # ${CMAKE_CURRENT_SOURCE_DIR}/spi
)

# Library names (kann von Parent-Projekt überschrieben werden)
if(NOT DEFINED HW_API_CORE_LIBNAME)
    set(HW_API_CORE_LIBNAME "hw_api_core")
endif()

if(NOT DEFINED HW_API_GPIO_LIBNAME)
    set(HW_API_GPIO_LIBNAME "hw_api_gpio")
endif()

if(NOT DEFINED HW_API_SPI_LIBNAME)
    set(HW_API_SPI_LIBNAME "hw_api_spi")
endif()

if(NOT DEFINED HW_API_PLATFORM_LIBNAME)
    set(HW_API_PLATFORM_LIBNAME "hw_api_platform")
endif()

# Subdirectories
add_subdirectory(core)
add_subdirectory(gpio)
add_subdirectory(platform)
add_subdirectory(drivers)
add_subdirectory(spi)

# Main HW_API library that combines all components
add_library(hw_api INTERFACE)

target_link_libraries(hw_api INTERFACE
    ${HW_API_CORE_LIBNAME}
    ${HW_API_GPIO_LIBNAME}
    ${HW_API_PLATFORM_LIBNAME}
    ${HW_API_SPI_LIBNAME}
)

target_include_directories(hw_api INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/spi
)