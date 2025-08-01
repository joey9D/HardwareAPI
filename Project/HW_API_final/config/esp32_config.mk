# ESP32 Hardware Configuration
# This file contains hardware-specific configurations for ESP32-C6 DevKitC-1

#===============================================================================
# Default Configuration for ESP32
#===============================================================================
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= ESP32
DEBUG_PROBE ?= esptool

# Default to ESP32-C6 for initial implementation
MCU_FAMILY ?= esp32c6
ESP32_FAMILY ?= esp32c6
ESP32_SPECIFIC ?= ESP32C6-DEVKITC-1
ESP32_IDF_TARGET ?= esp32c6

#===============================================================================
# ESP32-C6 DevKitC-1 Configuration
#===============================================================================

ifeq ($(MCU_FAMILY),esp32c6)
    # ESP32-C6 DevKitC-1 Board Configuration
    ESP32_FAMILY := esp32c6
    ESP32_SPECIFIC := ESP32C6-DEVKITC-1
    ESP32_IDF_TARGET := esp32c6
    ESP32_IDF_REPO ?= https://github.com/espressif/esp-idf.git
    ESP32_IDF_TAG ?= v5.1.2
    CORTEX_TYPE := riscv32imc
    DEFAULT_MCU := ESP32C6
    
    # ESP32-C6 DevKitC-1 specific pin definitions
    # LED: GPIO8 (built-in RGB LED)
    # Button: GPIO9 (BOOT button)
    ESP32_LED_PIN := 8
    ESP32_BUTTON_PIN := 9
    
else
    $(error ESP32 configuration currently only supports esp32c6 (ESP32-C6 DevKitC-1). Please set MCU_FAMILY=esp32c6)
endif

# ESP32-IDF Path Detection
ifndef ESP32_IDF_PATH
    # Try to detect ESP-IDF installation
    ESP32_IDF_PATH := $(shell which idf.py 2>/dev/null | xargs dirname 2>/dev/null)
    ifeq ($(ESP32_IDF_PATH),)
        ESP32_IDF_PATH := $(HOME)/esp/esp-idf
    endif
endif

#===============================================================================
# Configuration Summary for ESP32
#===============================================================================
# Board: ESP32-C6 DevKitC-1
# Family: $(ESP32_FAMILY)
# Specific: $(ESP32_SPECIFIC)  
# IDF Target: $(ESP32_IDF_TARGET)
# IDF Path: $(ESP32_IDF_PATH)
# Debug Probe: $(DEBUG_PROBE)
# Default MCU: $(DEFAULT_MCU)
# Architecture: $(CORTEX_TYPE)
# LED Pin: GPIO$(ESP32_LED_PIN) (RGB LED)
# Button Pin: GPIO$(ESP32_BUTTON_PIN) (BOOT button)
