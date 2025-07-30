# STM32 Cross-Compile Toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ARM GCC Toolchain paths for Windows (STM32CubeCLT installation)
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# Find STM32CubeCLT installation automatically
set(STM32_CUBECLT_PATHS
    "C:/ST/STM32CubeCLT_1.18.0/GNU-tools-for-STM32/bin"
    "C:/ST/STM32CubeCLT_1.17.0/GNU-tools-for-STM32/bin"
    "C:/ST/STM32CubeCLT/GNU-tools-for-STM32/bin"
)

# Try to find the toolchain in known locations
foreach(TOOLCHAIN_PATH ${STM32_CUBECLT_PATHS})
    if(EXISTS "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")
        set(TOOLCHAIN_BIN_PATH ${TOOLCHAIN_PATH})
        break()
    endif()
endforeach()

if(NOT TOOLCHAIN_BIN_PATH)
    message(FATAL_ERROR "STM32 ARM GCC Toolchain not found! Please install STM32CubeCLT from https://www.st.com/en/development-tools/stm32cubeclt.html")
endif()

message(STATUS "Found STM32 ARM GCC Toolchain at: ${TOOLCHAIN_BIN_PATH}")

# Set ARM Toolchain paths with Windows paths
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe)

# Set additional tools with full paths
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objcopy.exe CACHE STRING "objcopy tool")
set(CMAKE_SIZE_UTIL ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}size.exe CACHE STRING "size tool")
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objdump.exe CACHE STRING "objdump tool")

# Check if ARM GCC was found
if(NOT EXISTS ${CMAKE_C_COMPILER})
    message(FATAL_ERROR "ARM GCC Toolchain not found at: ${CMAKE_C_COMPILER}")
endif()

message(STATUS "Using ARM GCC Toolchain:")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  ASM Compiler: ${CMAKE_ASM_COMPILER}")

# Compiler-specific options for ARM Cortex-M
set(COMMON_FLAGS "-mcpu=cortex-m0plus -mthumb -mfloat-abi=soft")
set(COMMON_FLAGS "${COMMON_FLAGS} -ffunction-sections -fdata-sections")
set(COMMON_FLAGS "${COMMON_FLAGS} -Wall -Wextra")

# C flags
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
set(CMAKE_C_FLAGS_DEBUG_INIT "-g -O0")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O2 -DNDEBUG")

# C++ flags
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++17 -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2 -DNDEBUG")

# ASM flags
set(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS}")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections -Wl,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -specs=nano.specs -specs=nosys.specs")

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
