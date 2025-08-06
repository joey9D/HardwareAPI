cmake_minimum_required(VERSION 3.22)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Project Configuration
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# ESP-IDF must be included BEFORE project() call

# Determine if we're building for ESP32 or STM32
if(NOT DEFINED TARGET_PLATFORM)
    # If running under ESP-IDF, default to ESP32
    if(DEFINED ENV{IDF_PATH})
        set(TARGET_PLATFORM "ESP32")
        message(STATUS "ESP-IDF environment detected - defaulting to ESP32")
    else()
        message(FATAL_ERROR "TARGET_PLATFORM not defined. Please build via Makefile: make stm32 or make esp32")
    endif()
endif()

message(STATUS "Target Platform: ${TARGET_PLATFORM}")

# ESP32 Build Configuration
if(TARGET_PLATFORM STREQUAL "ESP32")
    # Load ESP32 configuration from config file
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config/esp32_config.mk")
        file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/config/esp32_config.mk" ESP32_CONFIG_CONTENT)
        foreach(LINE ${ESP32_CONFIG_CONTENT})
            # Parse lines with format: VARIABLE ?= value or VARIABLE := value or VARIABLE = value
            # Skip comments and empty lines
            if(NOT LINE MATCHES "^[ \t]*#" AND NOT LINE MATCHES "^[ \t]*$")
                if(LINE MATCHES "^([A-Za-z0-9_]+)[ \t]*[?:]?=[ \t]*(.*)$")
                    string(STRIP "${CMAKE_MATCH_2}" CONFIG_VALUE)
                    # Remove quotes if present
                    string(REGEX REPLACE "^\"(.*)\"$" "\\1" CONFIG_VALUE "${CONFIG_VALUE}")
                    set(${CMAKE_MATCH_1} "${CONFIG_VALUE}")
                    message(STATUS "ESP32 Config: ${CMAKE_MATCH_1}=${CONFIG_VALUE}")
                endif()
            endif()
        endforeach()
    else()
        message(FATAL_ERROR "ESP32 config file not found: ${CMAKE_CURRENT_SOURCE_DIR}/config/esp32_config.mk - Required for ESP32 build")
    endif()
    
    # Validate required variables from config
    if(NOT DEFINED MCU_FAMILY)
        message(FATAL_ERROR "MCU_FAMILY not defined in esp32_config.mk")
    endif()
    
    if(NOT DEFINED MCU_SPECIFIC)
        message(FATAL_ERROR "MCU_SPECIFIC not defined in esp32_config.mk")
    endif()
    
    if(NOT DEFINED ESP32_IDF_TARGET)
        message(FATAL_ERROR "ESP32_IDF_TARGET not defined in esp32_config.mk")
    endif()
    
    if(NOT DEFINED DEBUG_PROBE)
        message(FATAL_ERROR "DEBUG_PROBE not defined in esp32_config.mk")
    endif()
    
    # Display loaded configuration
    message(STATUS "Loaded ESP32 configuration:")
    message(STATUS "  MCU Family: ${MCU_FAMILY}")
    message(STATUS "  MCU Specific: ${MCU_SPECIFIC}")
    message(STATUS "  ESP32 IDF Target: ${ESP32_IDF_TARGET}")
    message(STATUS "  Debug Probe: ${DEBUG_PROBE}")
    message(STATUS "  ESP32 IDF Path: ${ESP32_IDF_PATH}")
    if(DEFINED ESP32_PORT)
        message(STATUS "  ESP32 Port: ${ESP32_PORT}")
    endif()
    
    # ESP-IDF Integration - Include ESP-IDF build system
    if(DEFINED ENV{IDF_PATH})
        message(STATUS "Using ESP-IDF from: $ENV{IDF_PATH}")
        
        # Set ESP-IDF target BEFORE project() call
        set(IDF_TARGET ${ESP32_IDF_TARGET})
        message(STATUS "Setting IDF_TARGET to: ${IDF_TARGET}")
        
        # Set component directories for ESP-IDF
        set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/components")
        
        # Include ESP-IDF build system
        include($ENV{IDF_PATH}/tools/cmake/project.cmake)
        
        # Define ESP-IDF project
        project(hw_api_esp32)
    else()
        message(FATAL_ERROR "ESP-IDF environment not found. Please source the ESP-IDF export script first.")
    endif()
else()
    # Regular project setup for STM32 and other platforms
    # For STM32, set the toolchain file before project()
    if(TARGET_PLATFORM STREQUAL "STM32")
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchains/stm32-toolchain.cmake")
        message(STATUS "Using STM32 toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
        
        # Check MCU_FAMILY and MCU_SPECIFIC
        if(NOT DEFINED MCU_FAMILY)
            message(FATAL_ERROR "MCU_FAMILY not defined. Please build via Makefile: make stm32")
        endif()
        
        if(NOT DEFINED MCU_SPECIFIC)
            message(FATAL_ERROR "MCU_SPECIFIC not defined. Please build via Makefile: make stm32")
        endif()
    endif()
    
    message(STATUS "Target Platform: ${TARGET_PLATFORM}")
    
    project(HW_API_Project 
        VERSION 1.0.0
        DESCRIPTION "Hardware Abstraction Layer for Embedded Systems"
        LANGUAGES C CXX ASM
    )
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific validation and settings
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    # Display STM32 configuration
    message(STATUS "MCU Family: ${MCU_FAMILY}")
    message(STATUS "MCU Specific: ${MCU_SPECIFIC}")
    message(STATUS "Debug Probe: ${DEBUG_PROBE}")
    
    # STM32 specific project settings
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    
    # Build type configuration (for STM32 platforms)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif()
    
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
    # ESP32-specific definitions handled by ESP-IDF
    add_compile_definitions(
        ESP32_PLATFORM=1
    )
    
    # Optional: Enable C++ exceptions for ESP32 (uncomment if needed)
    # Note: This increases binary size and may impact performance
    # add_compile_options(-fexceptions)
    # add_compile_options(-frtti)
    
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}. Supported: STM32, ESP32")
endif()

# Include directories (platform-specific)
if(TARGET_PLATFORM STREQUAL "STM32")
    # STM32: Use traditional include directories
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/HW_API
    )
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32: Include directories are handled by ESP-IDF component system
    # Components will automatically include their INCLUDE_DIRS
    message(STATUS "ESP32 platform: Include directories handled by ESP-IDF component system")
endif()

# Add subdirectories and finalize configuration
if(TARGET_PLATFORM STREQUAL "ESP32")
    # For ESP32, we already integrated with ESP-IDF above
    message(STATUS "ESP32 platform: Using ESP-IDF component system")
    
    # ESP-IDF will automatically find and process components in the components/ directory
    # Our hw_api component is located in components/hw_api/
    # Our main component is located in main/
    message(STATUS "ESP-IDF components will be loaded automatically from components/ and main/")
    
else()
    # For STM32, use traditional CMake subdirectories
    message(STATUS "Adding subdirectories for STM32...")
    
    # Add HW_API library
    add_subdirectory(HW_API)
    
    # STM32: app directory as normal CMake executable
    add_subdirectory(app)
    message(STATUS "Added STM32 app directory")
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
