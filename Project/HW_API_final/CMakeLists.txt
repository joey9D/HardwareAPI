cmake_minimum_required(VERSION 3.22)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Project Configuration
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# ESP-IDF must be included BEFORE project() call

# Target platform configuration
# COMMENTED OUT: ESP-IDF handles this automatically
if(NOT DEFINED TARGET_PLATFORM)
     message(FATAL_ERROR "TARGET_PLATFORM not defined. Please build via Makefile: make stm32 or make esp32")
endif()

message(STATUS "Target Platform: ${TARGET_PLATFORM}")

# ESP-IDF Integration - MUST come before project()
# COMMENTED OUT: ESP-IDF handles platform detection automatically
if(TARGET_PLATFORM STREQUAL "ESP32")
    if(NOT DEFINED MCU_FAMILY)
        message(FATAL_ERROR "MCU_FAMILY not defined. Please build via Makefile: make esp32")
    endif()
    
    if(NOT DEFINED MCU_SPECIFIC)
        message(FATAL_ERROR "MCU_SPECIFIC not defined. Please build via Makefile: make esp32")
    endif()
endif()

# ESP-IDF Integration - Auto-detection if ESP-IDF environment is present AND we're building for ESP32
if(DEFINED ENV{IDF_PATH} AND TARGET_PLATFORM STREQUAL "ESP32")
    # ESP-IDF environment detected - use ESP-IDF build system
    message(STATUS "ESP-IDF environment detected - using ESP-IDF build system for ESP32")
    
    # Include ESP-IDF build system BEFORE project()
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    
    # ESP-IDF project setup
    project(hw_api_esp32)
    
    # Set platform for our code
    set(TARGET_PLATFORM "ESP32")
    set(MCU_FAMILY "esp32c6")
    set(MCU_SPECIFIC "ESP32C6-DEVKITC-1")
    set(ESP32_IDF_TARGET "esp32c6")
    set(DEBUG_PROBE "esptool")
    
else()
    # Regular project setup for STM32 and other platforms
    # For STM32, set the toolchain file before project()
    if(TARGET_PLATFORM STREQUAL "STM32")
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchains/stm32-toolchain.cmake")
        message(STATUS "Using STM32 toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
    endif()
    
    # Check if called from our Makefile with proper variables
    if(NOT DEFINED TARGET_PLATFORM)
        message(FATAL_ERROR "TARGET_PLATFORM not defined. Please build via Makefile: make stm32")
    endif()
    
    message(STATUS "Target Platform: ${TARGET_PLATFORM}")
    
    project(HW_API_Project 
        VERSION 1.0.0
        DESCRIPTION "Hardware Abstraction Layer for Embedded Systems"
        LANGUAGES C CXX ASM
    )
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific validation
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    if(NOT DEFINED MCU_FAMILY)
        message(FATAL_ERROR "MCU_FAMILY not defined. Please build via Makefile: make stm32")
    endif()
    
    if(NOT DEFINED MCU_SPECIFIC)
        message(FATAL_ERROR "MCU_SPECIFIC not defined. Please build via Makefile: make stm32")
    endif()
    
    message(STATUS "MCU Family: ${MCU_FAMILY}")
    message(STATUS "MCU Specific: ${MCU_SPECIFIC}")
    message(STATUS "Debug Probe: ${DEBUG_PROBE}")
    
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32 validation already done above - display again for consistency
    message(STATUS "MCU Family: ${MCU_FAMILY}")
    message(STATUS "MCU Specific: ${MCU_SPECIFIC}")
    message(STATUS "ESP32 IDF Target: ${ESP32_IDF_TARGET}")
    message(STATUS "Debug Probe: ${DEBUG_PROBE}")
    
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}. Supported: STM32, ESP32")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Project settings (applied after project() call)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    # STM32 specific project settings
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# Build type configuration (for non-ESP32 platforms)
if(NOT CMAKE_BUILD_TYPE AND TARGET_PLATFORM STREQUAL "STM32")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Global compiler flags
if(TARGET_PLATFORM STREQUAL "STM32")
    # STM32-specific compiler flags
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
        add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
            -Wno-unused-parameter
        )
        
        # Debug-specific flags
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_compile_options(-g -O0)
            add_compile_definitions(DEBUG=1)
        endif()
        
        # Release-specific flags
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            add_compile_options(-O3)
            add_compile_definitions(NDEBUG=1)
        endif()
    endif()
    
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32-specific compiler flags
    add_compile_options(
        -Wall
        -Wextra
        -Wno-unused-parameter
        -Wno-sign-compare
    )
    
    # ESP32 specific compile definitions
    add_compile_definitions(
        ESP32_PLATFORM=1
        ESP_PLATFORM=1
    )
    
    # Debug-specific flags for ESP32
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -Og)
        add_compile_definitions(DEBUG=1)
    endif()
    
    # Release-specific flags for ESP32
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-Os)  # Optimize for size on ESP32
        add_compile_definitions(NDEBUG=1)
    endif()
endif()

# Include directories (platform-specific)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/HW_API
)

# Platform-specific include directories
if(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32-specific includes will be added by HW_API module
    message(STATUS "ESP32 platform detected - ESP32-specific includes will be configured by modules")
endif()

# Add subdirectories in correct order
message(STATUS "Adding subdirectories...")

# HW_API für beide Plattformen
add_subdirectory(HW_API)

# Platform-specific app/main directories
if(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32: main Verzeichnis als ESP-IDF main component
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main/CMakeLists.txt")
        add_subdirectory(main)
        message(STATUS "Added ESP32 main directory")
    else()
        message(STATUS "ESP32 main directory not found - ESP-IDF will handle main component automatically")
    endif()
elseif(TARGET_PLATFORM STREQUAL "STM32")
    # STM32: app Verzeichnis als normale CMake executable
    add_subdirectory(app)
    message(STATUS "Added STM32 app directory")
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM for subdirectories: ${TARGET_PLATFORM}")
endif()


# Print final configuration
message(STATUS "=======================================================")
message(STATUS "=== Configuration Summary ===")
message(STATUS "=======================================================")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
    message(STATUS "Cross-compiling: ${CMAKE_CROSSCOMPILING}")
    if(CMAKE_CROSSCOMPILING)
        message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")
        message(STATUS "Target processor: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
endif()

message(STATUS "=======================================================")

# Custom targets for development
add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo "============================================="
    COMMAND ${CMAKE_COMMAND} -E echo "=== HW_API Project Information ==="
    COMMAND ${CMAKE_COMMAND} -E echo "Project: ${PROJECT_NAME} v${PROJECT_VERSION}"
    COMMAND ${CMAKE_COMMAND} -E echo "Target Platform: ${TARGET_PLATFORM}"
    COMMAND ${CMAKE_COMMAND} -E echo "Build Type: ${CMAKE_BUILD_TYPE}"
    COMMAND ${CMAKE_COMMAND} -E echo "Source Dir: ${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "Binary Dir: ${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "=============================================="
    COMMENT "Display project information"
)
