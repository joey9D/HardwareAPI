# HW_API - Hardware Abstraction Layer
cmake_minimum_required(VERSION 3.22)

# Project information
message(STATUS "=== HW_API Module Configuration ===")
message(STATUS "Configuring Hardware Abstraction Layer...")

# Global include directories for HW_API
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Platform-specific configuration
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring for STM32 platform")
    
    # STM32-specific includes
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/stm32
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers/stm32_hal_wrapper
    )
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()

# Add core module (always required)
message(STATUS "Adding core module...")
add_subdirectory(core)

# Add platform-specific drivers
message(STATUS "Adding drivers module...")
if(TARGET_PLATFORM STREQUAL "STM32")
    add_subdirectory(drivers/stm32_hal_wrapper)
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM for drivers: ${TARGET_PLATFORM}")
endif()

# Add GPIO module
message(STATUS "Adding GPIO module...")
add_subdirectory(gpio)

# Add platform-specific implementations
message(STATUS "Adding platform module...")
if(TARGET_PLATFORM STREQUAL "STM32")
    add_subdirectory(platform/stm32/)
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM for platform: ${TARGET_PLATFORM}")
endif()

# Add SPI module
message(STATUS "Adding SPI module...")
# add_subdirectory(spi)

# Debug probes configuration (only for STM32 platform)
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

# Create HW_API library target
message(STATUS "Creating HW_API library target...")

# Collect all source files from subdirectories
# Note: Individual subdirectories will define their own library targets
# This main CMakeLists.txt coordinates the overall configuration

message(STATUS "=== HW_API Module Configuration Complete ===")