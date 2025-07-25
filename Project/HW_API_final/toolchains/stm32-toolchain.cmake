# STM32 Cross-Compile Toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Toolchain paths - try STM32CubeCLT first, then fallback to Arm GNU Toolchain
if(EXISTS "C:/ST/STM32CubeCLT_1.18.0/GNU-tools-for-STM32/bin/arm-none-eabi-gcc.exe")
    set(TOOLCHAIN_PREFIX "C:/ST/STM32CubeCLT_1.18.0/GNU-tools-for-STM32/bin/arm-none-eabi")
elseif(EXISTS "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/arm-none-eabi-gcc.exe")
    set(TOOLCHAIN_PREFIX "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/arm-none-eabi")
else()
    # Fallback to PATH
    set(TOOLCHAIN_PREFIX "arm-none-eabi")
endif()

# Toolchain
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc.exe)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++.exe)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc.exe)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}-ar.exe)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy.exe)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump.exe)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size.exe)

# Compiler flags
set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb -fdata-sections -ffunction-sections -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -std=c++17")

# Linker flags for bare metal
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m0plus -mthumb -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_CURRENT_SOURCE_DIR}/toolchains/stm32c031c6.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=output.map,--cref")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")

# Don't try to create shared libraries
set(BUILD_SHARED_LIBS OFF)

# HW_API Platform Configuration
set(TARGET_PLATFORM "STM32")
set(STM32_MCU_FAMILY "STM32C0xx")

# HAL Path will be handled by the HAL wrapper CMakeLists.txt
# Don't set a default here to allow FetchContent to work

# Search paths
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
