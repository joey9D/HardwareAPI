# ESP32 Hardware Configuration
# This file contains hardware-specific configurations for ESP32-C6 DevKitC-1

#===============================================================================
# Default Configuration for ESP32
#===============================================================================
# build-esp32
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= ESP32
DEBUG_PROBE ?= esptool

# Default to ESP32-C6 for initial implementation
MCU_FAMILY ?= esp32c6
MCU_SPECIFIC ?= ESP32C6-DEVKITC-1
ESP32_IDF_TARGET ?= esp32c6

# ESP32-IDF Path (can be overridden by environment variable)
ESP32_IDF_PATH ?= C:/Espressif/frameworks/esp-idf-v5.3.1

# ESP32 Serial Port (adjust as needed)
ESP32_PORT ?= COM8
ESP32_BAUD ?= 460800

# ESP32 Export Script Path
ESP32_EXPORT_BAT ?= C:\Espressif\frameworks\esp-idf-v5.3.1\export.bat

#===============================================================================
# ESP32-C6 DevKitC-1 Configuration
#===============================================================================
ifeq ($(MCU_FAMILY),esp32c6)
    # ESP32-C6 DevKitC-1 Board Configuration
    ESP32_IDF_TARGET := esp32c6
    CORTEX_TYPE := riscv32imc
    DEFAULT_MCU := ESP32C6    
else
    $(error ESP32 configuration currently only supports esp32c6 (ESP32-C6 DevKitC-1). Please set MCU_FAMILY=esp32c6)
endif

#===============================================================================
# Configuration Summary for ESP32
#===============================================================================
# Board: ESP32-C6 DevKitC-1
# Family: $(MCU_FAMILY)
# Specific: $(MCU_SPECIFIC)  
# IDF Target: $(ESP32_IDF_TARGET)
# IDF Path: $(ESP32_IDF_PATH)
# Debug Probe: $(DEBUG_PROBE)
# Default MCU: $(DEFAULT_MCU)
# Architecture: $(CORTEX_TYPE)
# LED Pin: GPIO$(ESP32_LED_PIN) (RGB LED)
# Button Pin: GPIO$(ESP32_BUTTON_PIN) (BOOT button)
