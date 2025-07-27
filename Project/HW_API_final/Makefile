

# HW_API Build System
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
TARGET_PLATFORM ?= STM32

# Platform-specific configuration
ifeq ($(TARGET_PLATFORM),STM32)
    TOOLCHAIN_FILE = toolchains/stm32-toolchain.cmake
    EXTRA_CMAKE_ARGS = -DSTM32_MCU_FAMILY=STM32C0xx
    ifdef STM32_HAL_PATH
        EXTRA_CMAKE_ARGS += -DSTM32_HAL_PATH=$(STM32_HAL_PATH)
    endif
# else ifeq ($(TARGET_PLATFORM),ESP32)
#     ifdef IDF_PATH
#         EXTRA_CMAKE_ARGS = -DIDF_PATH=$(IDF_PATH)
#     endif
endif

# Base CMake command
CMAKE_CMD = cmake -S . -B $(BUILD_DIR) -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTARGET_PLATFORM=$(TARGET_PLATFORM)

ifdef TOOLCHAIN_FILE
    CMAKE_CMD += -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE)
endif

CMAKE_CMD += $(EXTRA_CMAKE_ARGS)

# Default target
.PHONY: all clean prepare test stm32 esp32 info help

all: info
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD)
	cmake --build $(BUILD_DIR) -j

# Platform-specific builds
stm32:
	@$(MAKE) all TARGET_PLATFORM=STM32

# esp32:
# 	@$(MAKE) all TARGET_PLATFORM=ESP32


# Build with specific STM32 HAL path
stm32-hal:
ifndef STM32_HAL_PATH
	@echo "Error: STM32_HAL_PATH not set"
	@echo "Usage: make stm32-hal STM32_HAL_PATH=/path/to/hal"
	@exit 1
endif
	@$(MAKE) stm32 STM32_HAL_PATH=$(STM32_HAL_PATH)

# Build with specific ESP-IDF path - DISABLED FOR STM32-ONLY BUILD
# esp32-idf:
# ifndef IDF_PATH
# 	@echo "Error: IDF_PATH not set"
# 	@echo "Usage: make esp32-idf IDF_PATH=/path/to/esp-idf"
# 	@exit 1
# endif
# 	@$(MAKE) esp32 IDF_PATH=$(IDF_PATH)

# Hardware-specific targets (if supported by platform implementation)
flash erase reset debug:
	@if [ -f "$(BUILD_DIR)/build.ninja" ]; then \
		cmake --build $(BUILD_DIR) --target $@ || echo "Target '$@' not available for $(TARGET_PLATFORM)"; \
	else \
		echo "Build directory not found. Run 'make all' first."; \
	fi

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
ifdef TOOLCHAIN_FILE
	@echo "Toolchain File: $(TOOLCHAIN_FILE)"
endif
ifdef STM32_HAL_PATH
	@echo "STM32 HAL Path: $(STM32_HAL_PATH)"
endif
# ifdef IDF_PATH
# 	@echo "ESP-IDF Path: $(IDF_PATH)"
# endif
	@echo "CMake Command: $(CMAKE_CMD)"
	@echo "=================================="

# Help target
help:
	@echo "HW_API Makefile - Hardware Abstraction Layer Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make [target] [TARGET_PLATFORM=STM32|TEST] [BUILD_TYPE=Debug|Release]"
	@echo ""
	@echo "Targets:"
	@echo "  all              - Build for specified platform (default: STM32)"
	@echo "  stm32            - Build for STM32 platform"
	@echo "  # esp32            - Build for ESP32 platform (DISABLED)" 
	@echo "  # test             - Build for TEST platform (desktop) (DISABLED)"
	@echo "  stm32-hal        - Build STM32 with custom HAL path"
	@echo "  # esp32-idf        - Build ESP32 with custom IDF path (DISABLED)"
	@echo "  clean            - Clean build directory"
	@echo "  prepare          - Prepare fresh build directory"
	@echo "  info             - Show current build configuration"
	@echo "  dependency       - Generate dependency graph"
	@echo "  flash/erase/reset/debug - Hardware-specific operations"
	@echo ""
	@echo "Examples:"
	@echo "  make stm32"
	@echo "  # make esp32 BUILD_TYPE=Release (DISABLED)"
	@echo "  make stm32-hal STM32_HAL_PATH=/opt/STM32Cube/STM32CubeC0/Drivers/STM32C0xx_HAL_Driver"
	@echo "  # make esp32-idf IDF_PATH=/opt/esp-idf (DISABLED)"
	@echo "  make all TARGET_PLATFORM=STM32 BUILD_TYPE=Release"
