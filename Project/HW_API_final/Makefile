

# HW_API Build System
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= STM32

# Platform-specific configuration
ifeq ($(TARGET_PLATFORM),STM32)
    TOOLCHAIN_FILE = toolchains/stm32-toolchain.cmake
    EXTRA_CMAKE_ARGS = -DSTM32_MCU_FAMILY=STM32C0xx
    
    # Debug probe configuration (default: ST-Link for STM32)
    DEBUG_PROBE ?= st-link
    EXTRA_CMAKE_ARGS += -DDEBUG_PROBE=$(DEBUG_PROBE)
endif

# Base CMake command
CMAKE_CMD = cmake -S . -B $(BUILD_DIR) -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTARGET_PLATFORM=$(TARGET_PLATFORM)

ifdef TOOLCHAIN_FILE
    CMAKE_CMD += -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)
endif

CMAKE_CMD += $(EXTRA_CMAKE_ARGS)

# Default target
.PHONY: all clean prepare stm32 info help flash erase reset debug

all: info
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD)
	cmake --build $(BUILD_DIR) -j

# Platform-specific builds
stm32:
	$(MAKE) all TARGET_PLATFORM=STM32

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
	@echo "  make jlink                              # Build with J-Link probe"
	@echo "  make flash                              # Flash with current probe"
	@echo "  make flash-jlink                        # Flash with J-Link"
	@echo "  make stm32 DEBUG_PROBE=openocd          # Build with specific probe"
	@echo "  make stm32-hal STM32_HAL_PATH=/path/to/hal"
