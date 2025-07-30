# STM32 Cross-Compile Toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ARM GCC Toolchain paths (adjust if needed based on installation)
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# Set ARM Toolchain paths directly (we know they're in /opt/homebrew/bin)
set(CMAKE_C_COMPILER /opt/homebrew/bin/${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER /opt/homebrew/bin/${TOOLCHAIN_PREFIX}gcc)

# Set additional tools with full paths
set(CMAKE_OBJCOPY /opt/homebrew/bin/${TOOLCHAIN_PREFIX}objcopy CACHE STRING "objcopy tool")
set(CMAKE_SIZE_UTIL /opt/homebrew/bin/${TOOLCHAIN_PREFIX}size CACHE STRING "size tool")
set(CMAKE_OBJDUMP /opt/homebrew/bin/${TOOLCHAIN_PREFIX}objdump CACHE STRING "objdump tool")

# Check if ARM GCC was found
if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "ARM GCC Toolchain not found! Please install arm-none-eabi-gcc")
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
