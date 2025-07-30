cmake_minimum_required(VERSION 3.22)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Project Configuration
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
project(HW_API_Project 
    VERSION 1.0.0
    DESCRIPTION "Hardware Abstraction Layer for Embedded Systems"
    LANGUAGES C CXX ASM
)

# Project settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Target platform configuration
if(NOT DEFINED TARGET_PLATFORM)
    message(FATAL_ERROR "TARGET_PLATFORM not defined. Please build via Makefile: make stm32")
endif()

message(STATUS "Target Platform: ${TARGET_PLATFORM}")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific validation
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    if(NOT DEFINED STM32_FAMILY)
        message(FATAL_ERROR "STM32_FAMILY not defined. Please build via Makefile: make stm32")
    endif()
    
    if(NOT DEFINED STM32_MCU)
        message(FATAL_ERROR "STM32_MCU not defined. Please build via Makefile: make stm32")
    endif()
    
    message(STATUS "STM32 Family: ${STM32_FAMILY}")
    message(STATUS "STM32 MCU: ${STM32_MCU}")
    message(STATUS "Debug Probe: ${DEBUG_PROBE}")
endif()

# Global compiler flags
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

# Include directories (global)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/HW_API
)

# Add subdirectories in correct order
message(STATUS "Adding subdirectories...")
add_subdirectory(HW_API)
add_subdirectory(app)


# Print final configuration
message(STATUS "=== Configuration Summary ===")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
    message(STATUS "Cross-compiling: ${CMAKE_CROSSCOMPILING}")
    if(CMAKE_CROSSCOMPILING)
        message(STATUS "Target system: ${CMAKE_SYSTEM_NAME}")
        message(STATUS "Target processor: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
endif()

message(STATUS "==============================")

# Custom targets for development
add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo "=== HW_API Project Information ==="
    COMMAND ${CMAKE_COMMAND} -E echo "Project: ${PROJECT_NAME} v${PROJECT_VERSION}"
    COMMAND ${CMAKE_COMMAND} -E echo "Target Platform: ${TARGET_PLATFORM}"
    COMMAND ${CMAKE_COMMAND} -E echo "Build Type: ${CMAKE_BUILD_TYPE}"
    COMMAND ${CMAKE_COMMAND} -E echo "Source Dir: ${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "Binary Dir: ${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "=================================="
    COMMENT "Display project information"
    VERBATIM
)
