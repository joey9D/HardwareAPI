#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# HW_API - Hardware Abstraction Layer
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cmake_minimum_required(VERSION 3.22)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Project information
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "=== HW_API Module Configuration ===")
message(STATUS "Configuring Hardware Abstraction Layer...")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Global include directories for HW_API
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set C++ standard for all modules
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # No compiler-specific extensions

message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Global compiler warnings for all modules
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
    message(STATUS "Enabled GCC/Clang warnings: -Wall -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
    message(STATUS "Enabled MSVC warnings: /W4")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific configuration
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring for STM32 platform")
    
    # STM32 Hardware Configuration - Centralized for easy changes
    if(NOT DEFINED STM32_FAMILY)
        set(STM32_FAMILY "stm32c0" CACHE STRING "STM32 family (e.g., stm32c0, stm32g0, stm32f4)")
        message(STATUS "Using default STM32 family: ${STM32_FAMILY}")
    endif()
    
    message(STATUS "STM32 Family: ${STM32_FAMILY}")
    
    # STM32-specific includes (using configurable family)
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32/${STM32_FAMILY}
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/stm32_hal_wrapper
    )
    
    # Make STM32 configuration available to all modules
    set(STM32_PLATFORM_PATH "stm32/${STM32_FAMILY}" CACHE INTERNAL "STM32 platform path")
    set(STM32_HW_FILE "${STM32_FAMILY}_hw" CACHE INTERNAL "STM32 hardware file base name")
    
    # Global STM32 compile definitions
    add_compile_definitions(
        STM32_PLATFORM=1
        STM32_FAMILY_${STM32_FAMILY}=1
    )
    
    message(STATUS "STM32 Platform Path: ${STM32_PLATFORM_PATH}")
    message(STATUS "STM32 HW File Base: ${STM32_HW_FILE}")
    message(STATUS "STM32 compile definitions applied globally")
    
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add core module (always required)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Adding core module...")
add_subdirectory(core)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add platform-specific drivers
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Adding drivers module...")
if(TARGET_PLATFORM STREQUAL "STM32")
    add_subdirectory(drivers/stm32_hal_wrapper)
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM for drivers: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add GPIO module
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Adding GPIO module...")
add_subdirectory(gpio)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add platform-specific implementations
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Adding platform module...")
add_subdirectory(platform)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add SPI module
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Adding SPI module...")
# add_subdirectory(spi)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Debug probes configuration (only for STM32 platform)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring debug probes...")
    
    # Default debug probe
    if(NOT DEFINED DEBUG_PROBE)
        set(DEBUG_PROBE "st-link" CACHE STRING "Debug probe to use")
    endif()
    
    message(STATUS "Selected debug probe: ${DEBUG_PROBE}")
    
    # Include the appropriate debug probe configuration
    set(DEBUG_PROBE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/debug_probes/${DEBUG_PROBE}.cmake")
    
    if(EXISTS ${DEBUG_PROBE_FILE})
        message(STATUS "Including debug probe config: ${DEBUG_PROBE_FILE}")
        include(${DEBUG_PROBE_FILE})
    else()
        message(WARNING "Debug probe configuration not found: ${DEBUG_PROBE_FILE}")
        message(STATUS "Available debug probes in ${CMAKE_CURRENT_SOURCE_DIR}/debug_probes/:")
        file(GLOB DEBUG_PROBE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/debug_probes/*.cmake")
        foreach(PROBE_FILE ${DEBUG_PROBE_FILES})
            get_filename_component(PROBE_NAME ${PROBE_FILE} NAME_WE)
            message(STATUS "  - ${PROBE_NAME}")
        endforeach()
    endif()
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create HW_API library target
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Creating HW_API library target...")

# Collect all source files from subdirectories
# Note: Individual subdirectories will define their own library targets
# This main CMakeLists.txt coordinates the overall configuration

message(STATUS "=== HW_API Module Configuration Complete ===")