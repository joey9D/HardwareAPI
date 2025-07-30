

# HW_API Build System
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= STM32
TOOLCHAIN_FILE ?= toolchains/stm32-toolchain.cmake
MCU_FAMILY ?= stm32c0xx
MCU_SPECIFIC ?= STM32C031C6
DEBUG_PROBE ?= st-link

# STM32 HAL Repository Configuration (based on MCU_FAMILY)
ifeq ($(MCU_FAMILY),stm32c0xx)
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32c0xx_hal_driver.git
    STM32_HAL_TAG ?= v1.4.0
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_c0.git
    STM32_CMSIS_TAG ?= v1.3.0
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32C0xx
else ifeq ($(MCU_FAMILY),stm32g0xx)
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32g0xx_hal_driver.git
    STM32_HAL_TAG ?= v1.4.4
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_g0.git
    STM32_CMSIS_TAG ?= v1.4.2
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32G0xx
else ifeq ($(MCU_FAMILY),stm32f4xx)
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
    STM32_HAL_TAG ?= v1.8.2
    STM32_CMSIS_REPO ?= https://github.com/STMicroelectronics/cmsis_device_f4.git
    STM32_CMSIS_TAG ?= v2.6.8
    ARM_CMSIS_REPO ?= https://github.com/ARM-software/CMSIS_5.git
    ARM_CMSIS_TAG ?= 5.9.0
    HAL_PREFIX ?= STM32F4xx
endif

# Base CMake command (platform-specific configuration added in build targets)
CMAKE_CMD = cmake -S . -B $(BUILD_DIR) -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTARGET_PLATFORM=$(TARGET_PLATFORM)

# Default target
.PHONY: all clean prepare stm32 info help flash erase reset debug

all: info
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD)
	cmake --build $(BUILD_DIR) -j

# Platform-specific builds
stm32:
	@echo "=== Building STM32 Platform ==="
	@mkdir -p $(BUILD_DIR)
	@echo "Configuring build system..."
	@cmake -S . -B $(BUILD_DIR) -G "Ninja" \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DTARGET_PLATFORM=STM32 \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
		-DSTM32_FAMILY=$(MCU_FAMILY) \
		-DSTM32_MCU=$(MCU_SPECIFIC) \
		-DDEBUG_PROBE=$(DEBUG_PROBE) \
		-DSTM32_HAL_REPO=$(STM32_HAL_REPO) \
		-DSTM32_HAL_TAG=$(STM32_HAL_TAG) \
		-DSTM32_CMSIS_REPO=$(STM32_CMSIS_REPO) \
		-DSTM32_CMSIS_TAG=$(STM32_CMSIS_TAG) \
		-DARM_CMSIS_REPO=$(ARM_CMSIS_REPO) \
		-DARM_CMSIS_TAG=$(ARM_CMSIS_TAG) \
		-DHAL_PREFIX=$(HAL_PREFIX) > /dev/null
	@echo "Building project..."
	@cmake --build $(BUILD_DIR) -j

# ESP32 Build with all platform-specific settings (commented - currently disabled)
# esp32:
# 	@echo "=== Building ESP32 Platform ==="
# 	@mkdir -p $(BUILD_DIR)
# 	cmake -S . -B $(BUILD_DIR) -G "Ninja" \
# 		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
# 		-DTARGET_PLATFORM=ESP32 \
# 		-DESP32_FAMILY=esp32 \
# 		-DDEBUG_PROBE=esptool
# 	cmake --build $(BUILD_DIR) -j

# Hardware-specific targets (simplified)
flash erase reset debug:
	cmake --build $(BUILD_DIR) --target $@

# Utility targets
clean:
	@cmake -E rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory"

prepare:
	@cmake -E rm -rf $(BUILD_DIR)
	@cmake -E make_directory $(BUILD_DIR)
	@echo "Prepared fresh build directory"

# Development helpers
dependency:
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD) --graphviz=$(BUILD_DIR)/graph.dot
	@echo "Dependency graph generated at $(BUILD_DIR)/graph.dot"

# Show current configuration
info:
	@echo "=== HW_API Build Configuration ==="
	@echo "Target Platform: $(TARGET_PLATFORM)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
ifdef TOOLCHAIN_FILE
	@echo "Toolchain File: $(TOOLCHAIN_FILE)"
endif
ifdef STM32_HAL_PATH
	@echo "STM32 HAL Path: $(STM32_HAL_PATH)"
endif
	@echo "CMake Command: $(CMAKE_CMD)"
	@echo "Available debug probes: st-link, jlink, openocd"
	@echo "=================================="

# Help target
help:
	@echo "HW_API Makefile - Hardware Abstraction Layer Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make [target] [TARGET_PLATFORM=STM32] [BUILD_TYPE=Debug|Release] [DEBUG_PROBE=st-link|jlink|openocd]"
	@echo ""
	@echo "Build Targets:"
	@echo "  all              - Build for specified platform (default: STM32)"
	@echo "  stm32            - Build for STM32 platform"
	@echo "  stm32-hal        - Build STM32 with custom HAL path"
	@echo "  clean            - Clean build directory"
	@echo "  prepare          - Prepare fresh build directory"
	@echo "  info             - Show current build configuration"
	@echo "  dependency       - Generate dependency graph"
	@echo ""
	@echo "Debug Probe Targets:"
	@echo "  stlink           - Build with ST-Link debug probe"
	@echo "  jlink            - Build with J-Link debug probe"
	@echo "  openocd          - Build with OpenOCD debug probe"
	@echo ""
	@echo "Hardware Operations (use current DEBUG_PROBE):"
	@echo "  flash            - Flash firmware to target"
	@echo "  erase            - Erase target flash"
	@echo "  reset            - Reset target device"
	@echo "  debug            - Start debug session"
	@echo ""
	@echo "Hardware Operations (probe-specific):"
	@echo "  flash-stlink     - Flash using ST-Link"
	@echo "  flash-jlink      - Flash using J-Link"
	@echo "  flash-openocd    - Flash using OpenOCD"
	@echo "  (same pattern for erase-, reset-, debug-)"
	@echo ""
	@echo "Examples:"
	@echo "  make stm32                              # Build with default ST-Link"

