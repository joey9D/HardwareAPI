# HW_API Core Module
cmake_minimum_required(VERSION 3.22)

message(STATUS "=== Configuring HW_API Core Module ===")

# Collect all source files in current directory
file(GLOB_RECURSE CORE_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE CORE_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Display found files for debugging
message(STATUS "Core source files found:")
foreach(SOURCE_FILE ${CORE_SOURCES})
    get_filename_component(FILENAME ${SOURCE_FILE} NAME)
    message(STATUS "  - ${FILENAME}")
endforeach()

message(STATUS "Core header files found:")
foreach(HEADER_FILE ${CORE_HEADERS})
    get_filename_component(FILENAME ${HEADER_FILE} NAME)
    message(STATUS "  - ${FILENAME}")
endforeach()

# Filter platform-specific files based on TARGET_PLATFORM
set(FILTERED_SOURCES ${CORE_SOURCES})
set(FILTERED_HEADERS ${CORE_HEADERS})

if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Filtering for STM32 platform...")
    
    # Remove ESP32-specific files
    list(FILTER FILTERED_SOURCES EXCLUDE REGEX ".*esp32.*")
    list(FILTER FILTERED_HEADERS EXCLUDE REGEX ".*esp32.*")
    
    message(STATUS "Excluded ESP32-specific files for STM32 build")
    
elseif(TARGET_PLATFORM STREQUAL "TEST")
    message(STATUS "Including all files for TEST platform")
    
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in core module: ${TARGET_PLATFORM}")
endif()

# Create the core library
if(FILTERED_SOURCES)
    # Create static library with source files
    add_library(hw_api_core STATIC 
        ${FILTERED_SOURCES}
        ${FILTERED_HEADERS}  # Include headers in target for IDE support
    )
    
    message(STATUS "Created hw_api_core library with source files")
    
else()
    # Create interface library if no source files (header-only)
    add_library(hw_api_core INTERFACE)
    
    message(STATUS "Created hw_api_core as header-only interface library")
endif()

# Set include directories
target_include_directories(hw_api_core 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # Parent HW_API directory
)

# Platform-specific compile definitions
if(TARGET_PLATFORM STREQUAL "STM32")
    target_compile_definitions(hw_api_core PUBLIC
        STM32_PLATFORM=1
        HW_CORE_STM32=1
    )
elseif(TARGET_PLATFORM STREQUAL "TEST")
    target_compile_definitions(hw_api_core PUBLIC
        TEST_PLATFORM=1
        HW_CORE_TEST=1
    )
endif()

# Compiler-specific settings
if(FILTERED_SOURCES)
    target_compile_features(hw_api_core PUBLIC cxx_std_17)
    
    # Add compiler warnings for source files
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(hw_api_core PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )
    endif()
endif()

# Set library properties
set_target_properties(hw_api_core PROPERTIES
    OUTPUT_NAME "hw_api_core"
    EXPORT_NAME "Core"
)

message(STATUS "=== HW_API Core Module Configuration Complete ===")

# Export information for parent CMakeLists
set(HW_API_CORE_TARGET hw_api_core PARENT_SCOPE)
set(HW_API_CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)