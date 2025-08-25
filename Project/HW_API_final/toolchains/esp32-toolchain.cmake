# ESP32 Cross-Compile Toolchain
# ESP32-C6 uses RISC-V 32-bit architecture

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# RISC-V GCC Toolchain prefix for ESP32-C6
set(TOOLCHAIN_PREFIX riscv32-esp-elf-)

# ESP-IDF installation paths for Windows
# ESP-IDF typically installs RISC-V toolchain in these locations
set(ESP32_IDF_PATHS
    "$ENV{HOME}/.espressif/tools/riscv32-esp-elf"
    "C:/Espressif/tools/riscv32-esp-elf" 
    "$ENV{IDF_PATH}/tools/riscv32-esp-elf"
    "/opt/esp/tools/riscv32-esp-elf"
)

# Try to find the latest RISC-V toolchain version
set(TOOLCHAIN_BIN_PATH "")
foreach(ESP_PATH ${ESP32_IDF_PATHS})
    # Look for versioned directories (e.g., esp-12.2.0_20230208)
    file(GLOB TOOLCHAIN_VERSIONS "${ESP_PATH}/esp-*")
    if(TOOLCHAIN_VERSIONS)
        # Sort to get the latest version
        list(SORT TOOLCHAIN_VERSIONS)
        list(REVERSE TOOLCHAIN_VERSIONS)
        list(GET TOOLCHAIN_VERSIONS 0 LATEST_VERSION)
        
        # Check if the toolchain exists in this version
        set(TEST_PATH "${LATEST_VERSION}/riscv32-esp-elf/bin")
        if(EXISTS "${TEST_PATH}/${TOOLCHAIN_PREFIX}gcc.exe" OR EXISTS "${TEST_PATH}/${TOOLCHAIN_PREFIX}gcc")
            set(TOOLCHAIN_BIN_PATH ${TEST_PATH})
            get_filename_component(ESP32_TOOLCHAIN_VERSION ${LATEST_VERSION} NAME)
            break()
        endif()
    endif()
endforeach()

# Fallback: try common ESP-IDF installation paths directly
if(NOT TOOLCHAIN_BIN_PATH)
    set(ESP32_FALLBACK_PATHS
        "$ENV{HOME}/.espressif/tools/riscv32-esp-elf/esp-12.2.0_20230208/riscv32-esp-elf/bin"
        "C:/Espressif/tools/riscv32-esp-elf/esp-12.2.0_20230208/riscv32-esp-elf/bin"
        "$ENV{IDF_PATH}/tools/dist/riscv32-esp-elf/bin"
    )
    
    foreach(FALLBACK_PATH ${ESP32_FALLBACK_PATHS})
        if(EXISTS "${FALLBACK_PATH}/${TOOLCHAIN_PREFIX}gcc.exe" OR EXISTS "${FALLBACK_PATH}/${TOOLCHAIN_PREFIX}gcc")
            set(TOOLCHAIN_BIN_PATH ${FALLBACK_PATH})
            set(ESP32_TOOLCHAIN_VERSION "fallback")
            break()
        endif()
    endforeach()
endif()

if(NOT TOOLCHAIN_BIN_PATH)
    message(FATAL_ERROR 
        "ESP32 RISC-V GCC Toolchain not found!\n"
        "Please install ESP-IDF from: https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/get-started/\n"
        "Or set IDF_PATH environment variable to point to your ESP-IDF installation."
    )
endif()

message(STATUS "Found ESP32 RISC-V GCC Toolchain at: ${TOOLCHAIN_BIN_PATH}")
message(STATUS "Toolchain version: ${ESP32_TOOLCHAIN_VERSION}")

# Set RISC-V Toolchain paths (cross-platform compatibility)
if(WIN32)
    set(TOOLCHAIN_EXT ".exe")
else()
    set(TOOLCHAIN_EXT "")
endif()

set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXT})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}g++${TOOLCHAIN_EXT})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_EXT})

# Set additional tools with full paths
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objcopy${TOOLCHAIN_EXT} CACHE STRING "objcopy tool")
set(CMAKE_SIZE_UTIL ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}size${TOOLCHAIN_EXT} CACHE STRING "size tool")
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objdump${TOOLCHAIN_EXT} CACHE STRING "objdump tool")
set(CMAKE_NM ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}nm${TOOLCHAIN_EXT} CACHE STRING "nm tool")
set(CMAKE_STRIP ${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}strip${TOOLCHAIN_EXT} CACHE STRING "strip tool")

# Check if RISC-V GCC was found
if(NOT EXISTS ${CMAKE_C_COMPILER})
    message(FATAL_ERROR "RISC-V GCC Toolchain not found at: ${CMAKE_C_COMPILER}")
endif()

message(STATUS "Using ESP32 RISC-V GCC Toolchain:")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  ASM Compiler: ${CMAKE_ASM_COMPILER}")

# ESP32-C6 specific compiler flags (RISC-V 32-bit with IMC extensions)
set(ESP32_ARCH_FLAGS "-march=rv32imc_zicsr_zifencei")
set(ESP32_ABI_FLAGS "-mabi=ilp32")

# Common flags for ESP32-C6
set(COMMON_FLAGS "${ESP32_ARCH_FLAGS} ${ESP32_ABI_FLAGS}")
set(COMMON_FLAGS "${COMMON_FLAGS} -ffunction-sections -fdata-sections")
set(COMMON_FLAGS "${COMMON_FLAGS} -Wall -Wextra -Wno-unused-parameter")

# ESP32-specific optimization flags
set(COMMON_FLAGS "${COMMON_FLAGS} -fstrict-volatile-bitfields")
set(COMMON_FLAGS "${COMMON_FLAGS} -fno-jump-tables")

# C flags
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
set(CMAKE_C_FLAGS_DEBUG_INIT "-g -Og -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT "-Os -DNDEBUG")  # Optimize for size on ESP32

# C++ flags  
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -fno-threadsafe-statics")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Og -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Os -DNDEBUG")

# ASM flags
set(CMAKE_ASM_FLAGS_INIT "${ESP32_ARCH_FLAGS} ${ESP32_ABI_FLAGS}")

# Linker flags for ESP32
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--cref")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,--print-memory-usage")

# ESP32-specific defines
add_compile_definitions(
    ESP_PLATFORM=1
    ESP32C6=1
    RISCV=1
    WITH_POSIX=1
    CONFIG_IDF_TARGET_ESP32C6=1
    CONFIG_IDF_TARGET="esp32c6"
    IDF_VER="v5.3.1"
    SOC_RISCV_HAS_CLIC=1
    CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE=1
)

# ESP-IDF Path detection for includes
if(DEFINED ENV{IDF_PATH})
    set(ESP32_IDF_PATH "$ENV{IDF_PATH}")
    message(STATUS "ESP-IDF Path: ${ESP32_IDF_PATH}")
else()
    # Try to find ESP-IDF installation automatically
    set(ESP32_IDF_SEARCH_PATHS
        "C:/Espressif/Frameworks/esp-idf-v5.3.1"
        "C:/Espressif/frameworks/esp-idf-v5.1.2"
        "C:/Espressif/frameworks/esp-idf-v5.1.1"
        "C:/Espressif/frameworks/esp-idf-v5.2.0"
        "$ENV{HOME}/esp/esp-idf"
        "/opt/esp/idf"
    )
    
    foreach(IDF_SEARCH_PATH ${ESP32_IDF_SEARCH_PATHS})
        if(EXISTS "${IDF_SEARCH_PATH}/components")
            set(ESP32_IDF_PATH "${IDF_SEARCH_PATH}")
            message(STATUS "Found ESP-IDF Path: ${ESP32_IDF_PATH}")
            break()
        endif()
    endforeach()
    
    if(NOT ESP32_IDF_PATH)
        message(WARNING "IDF_PATH environment variable not set and ESP-IDF not found in standard locations. ESP-IDF components may not be found.")
    endif()
endif()

# Add ESP-IDF include directories if found
if(ESP32_IDF_PATH)
set(ESP32_IDF_INCLUDES
    "${ESP32_IDF_PATH}/components/esp_driver_gpio/include"
    "${ESP32_IDF_PATH}/components/esp_system/include"
    "${ESP32_IDF_PATH}/components/esp_common/include"
    "${ESP32_IDF_PATH}/components/esp_timer/include"
    "${ESP32_IDF_PATH}/components/esp_rom/include"
    "${ESP32_IDF_PATH}/components/esp_rom/include/esp32c6"
    "${ESP32_IDF_PATH}/components/freertos/FreeRTOS-Kernel/include"
    "${ESP32_IDF_PATH}/components/freertos/FreeRTOS-Kernel/portable/riscv/include/freertos"
    "${ESP32_IDF_PATH}/components/freertos/esp_additions/include"
    "${ESP32_IDF_PATH}/components/freertos/esp_additions/include/freertos"
    "${ESP32_IDF_PATH}/components/freertos/config/include"
    "${ESP32_IDF_PATH}/components/freertos/config/riscv/include"
    "${ESP32_IDF_PATH}/components/hal/include"
    "${ESP32_IDF_PATH}/components/hal/platform_port/include"
    "${ESP32_IDF_PATH}/components/hal/esp32c6/include"
    "${ESP32_IDF_PATH}/components/soc/include"
    "${ESP32_IDF_PATH}/components/soc/esp32c6/include"
    "${ESP32_IDF_PATH}/components/riscv/include"
    "${ESP32_IDF_PATH}/components/esp_hw_support/include"
    "${ESP32_IDF_PATH}/components/esp_hw_support/include/soc"
    "${ESP32_IDF_PATH}/components/esp_hw_support/port/esp32c6"
    "${ESP32_IDF_PATH}/components/esp_hw_support/port/esp32c6/private_include"
    "${ESP32_IDF_PATH}/components/log/include"
    "${ESP32_IDF_PATH}/components/heap/include"
    "${ESP32_IDF_PATH}/components/newlib/platform_include"
    "${ESP32_IDF_PATH}/components/spi_flash/include"
    "${ESP32_IDF_PATH}/components/nvs_flash/include"
    "${ESP32_IDF_PATH}/components/xtensa/include"
    # "${ESP32_IDF_PATH}/components/xtensa/esp32c6/include"
    "${ESP32_IDF_PATH}/components/esp_app_format/include"
    "${ESP32_IDF_PATH}/components/bootloader_support/include"
)    # Add include directories for cross-compilation
    foreach(IDF_INCLUDE_DIR ${ESP32_IDF_INCLUDES})
        if(EXISTS "${IDF_INCLUDE_DIR}")
            include_directories(SYSTEM "${IDF_INCLUDE_DIR}")
            message(STATUS "Added ESP-IDF include: ${IDF_INCLUDE_DIR}")
        endif()
    endforeach()
endif()

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set the target file extension for ESP32
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

message(STATUS "ESP32-C6 RISC-V Toolchain configuration complete!")
