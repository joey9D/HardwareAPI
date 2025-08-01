# STM32 Hardware Configuration
# This file contains hardware-specific configurations for different STM32 families

#===============================================================================
# Default Configuration
#===============================================================================
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= STM32
TOOLCHAIN_FILE ?= toolchains/stm32-toolchain.cmake
MCU_FAMILY ?= stm32g0xx
MCU_SPECIFIC ?= STM32G071RB
DEBUG_PROBE ?= st-link

#===============================================================================
# STM32 Family-Specific HAL Repository Configuration
#===============================================================================

ifeq ($(MCU_FAMILY),stm32c0xx)
    # STM32C0xx Family Configuration
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32c0xx_hal_driver.git
    STM32_HAL_TAG ?= v1.4.0
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_c0.git
    STM32_CMSIS_TAG ?= v1.3.0
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32C0xx
    CORTEX_TYPE ?= cortex-m0plus
    DEFAULT_MCU ?= STM32C031C6
    
else ifeq ($(MCU_FAMILY),stm32g0xx)
    # STM32G0xx Family Configuration
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32g0xx_hal_driver.git
    STM32_HAL_TAG ?= v1.4.4
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_g0.git
    STM32_CMSIS_TAG ?= v1.4.2
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32G0xx
    CORTEX_TYPE ?= cortex-m0plus
    DEFAULT_MCU ?= STM32G071RB
    
else ifeq ($(MCU_FAMILY),stm32f4xx)
    # STM32F4xx Family Configuration
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
    STM32_HAL_TAG ?= v1.8.2
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_f4.git
    STM32_CMSIS_TAG ?= v2.6.8
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32F4xx
    CORTEX_TYPE ?= cortex-m4
    DEFAULT_MCU ?= STM32F407VG
    
else
    $(error Unsupported MCU_FAMILY: $(MCU_FAMILY). Supported families: stm32c0xx, stm32g0xx, stm32f4xx)
endif

#===============================================================================
# Configuration Summary
#===============================================================================
# This section is purely informational and can be used for debugging
# Family: $(MCU_FAMILY)
# HAL Repo: $(STM32_HAL_REPO)
# HAL Version: $(STM32_HAL_TAG)
# CMSIS Repo: $(STM32_CMSIS_REPO)
# CMSIS Version: $(STM32_CMSIS_TAG)
# Default MCU: $(DEFAULT_MCU)
# Cortex Type: $(CORTEX_TYPE)
