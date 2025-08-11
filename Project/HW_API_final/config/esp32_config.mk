# ESP32 Hardware Configuration
# This file contains hardware-specific configurations for ESP32-C6 DevKitC-1

#================================================================================
# Default Configuration for ESP32
#================================================================================
# build-esp32
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= ESP32
DEBUG_PROBE ?= esptool

# ESP32 uses direct chip names (no families like STM32)
# Available targets: esp32, esp32s2, esp32s3, esp32c3, esp32c6, esp32h2, etc.
IDF_TARGET ?= esp32c6
BOARD ?= ESP32C6-DEVKITC-1

# ESP32-IDF Path (can be overridden by environment variable)
ESP32_IDF_PATH ?= C:/Espressif/frameworks/esp-idf-v5.3.1

# ESP32 Serial Port (adjust as needed)
ESP32_PORT ?= COM8
ESP32_BAUD ?= 460800

# ESP32 Export Script Path
ESP32_EXPORT_BAT ?= C:\Espressif\frameworks\esp-idf-v5.3.1\export.bat

#================================================================================
# ESP32-C6 DevKitC-1 Configuration
#================================================================================
ifeq ($(IDF_TARGET),esp32c6)
    # ESP32-C6 DevKitC-1 Board Configuration
    CHIP_ARCH := riscv32imc
    DEFAULT_CHIP := ESP32C6    
else ifeq ($(IDF_TARGET),esp32)
    # ESP32 Original Configuration
    CHIP_ARCH := xtensa
    DEFAULT_CHIP := ESP32
else ifeq ($(IDF_TARGET),esp32s2)
    # ESP32-S2 Configuration
    CHIP_ARCH := xtensa
    DEFAULT_CHIP := ESP32S2
else ifeq ($(IDF_TARGET),esp32s3)
    # ESP32-S3 Configuration
    CHIP_ARCH := xtensa
    DEFAULT_CHIP := ESP32S3
else ifeq ($(IDF_TARGET),esp32c3)
    # ESP32-C3 Configuration
    CHIP_ARCH := riscv32imc
    DEFAULT_CHIP := ESP32C3
else
    $(error ESP32 configuration supports: esp32, esp32s2, esp32s3, esp32c3, esp32c6. Please set IDF_TARGET=<chip>)
endif

#================================================================================
# Configuration Summary for ESP32
#================================================================================
# Board: $(BOARD)
# IDF Target: $(IDF_TARGET)
# IDF Path: $(ESP32_IDF_PATH)
# Debug Probe: $(DEBUG_PROBE)
# Default Chip: $(DEFAULT_CHIP)
# Architecture: $(CHIP_ARCH)
# Serial Port: $(ESP32_PORT)
