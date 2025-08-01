# ESP32 Hardware Configuration
# This file contains hardware-specific configurations for ESP32 family
# Currently disabled in main Makefile, but prepared for future use

#===============================================================================
# ESP32 Family Configuration (Future Implementation)
#===============================================================================

ifeq ($(TARGET_PLATFORM),ESP32)
    ESP32_FAMILY ?= esp32
    ESP32_SPECIFIC ?= ESP32-DEVKITC
    DEBUG_PROBE ?= esptool
    
    # ESP32 specific repositories and versions would go here
    # ESP32_IDF_REPO ?= https://github.com/espressif/esp-idf.git
    # ESP32_IDF_TAG ?= v5.0
    
    # ESP32 specific settings
    CORTEX_TYPE ?= xtensa-lx6
    DEFAULT_MCU ?= ESP32
endif

#===============================================================================
# Configuration Summary for ESP32
#===============================================================================
# Family: $(ESP32_FAMILY)
# Specific: $(ESP32_SPECIFIC)
# Debug Probe: $(DEBUG_PROBE)
# Default MCU: $(DEFAULT_MCU)
