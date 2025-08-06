
# HW_API Build System

# include config/esp32_config.mk  # ESP32-specific configuration  
include config/stm32_config.mk  # STM32-specific configuration (default)


# Base CMake command (platform-specific configuration added in build targets)
CMAKE_CMD = cmake -S . -B $(BUILD_DIR) -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTARGET_PLATFORM=$(TARGET_PLATFORM)

# Default target
.PHONY: all clean prepare stm32 esp32 info help flash erase reset debug

all: info
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD)
	cmake --build $(BUILD_DIR) -j

# Platform-specific builds
stm32:
	@echo "================================================="
	@echo "=== Building STM32 Platform ==="
	@echo "================================================="
	@mkdir -p $(BUILD_DIR)
	@echo "Configuring build system..."
	@cmake -S . -B $(BUILD_DIR) -G "Ninja" \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DTARGET_PLATFORM=STM32 \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
		-DMCU_FAMILY=$(MCU_FAMILY) \
		-DMCU_SPECIFIC=$(MCU_SPECIFIC) \
		-DDEBUG_PROBE=$(DEBUG_PROBE) \
		-DSTM32_HAL_REPO=$(STM32_HAL_REPO) \
		-DSTM32_HAL_TAG=$(STM32_HAL_TAG) \
		-DSTM32_CMSIS_REPO=$(STM32_CMSIS_REPO) \
		-DSTM32_CMSIS_TAG=$(STM32_CMSIS_TAG) \
		-DARM_CMSIS_REPO=$(ARM_CMSIS_REPO) \
		-DARM_CMSIS_TAG=$(ARM_CMSIS_TAG) \
		-DHAL_PREFIX=$(HAL_PREFIX)
	@echo "Building project..."
	@cmake --build $(BUILD_DIR) -j

# ESP32 Build with ESP-IDF (requires toolchain in PATH)
esp32:
	@echo "================================================="
	@echo "=== Building ESP32 Platform (ESP-IDF) ==="
	@echo "================================================="
	@echo "Setting ESP32 target to $(ESP32_IDF_TARGET)..."
	@python C:\Espressif\frameworks\esp-idf-v5.3.1\tools\idf.py set-target $(ESP32_IDF_TARGET)
	@echo ""
	@echo "Building ESP32 project..."
	@python C:\Espressif\frameworks\esp-idf-v5.3.1\tools\idf.py -D TARGET_PLATFORM=ESP32 -D MCU_FAMILY=$(MCU_FAMILY) -D MCU_SPECIFIC=$(MCU_SPECIFIC) -D ESP32_IDF_TARGET=$(ESP32_IDF_TARGET) -D CMAKE_BUILD_TYPE=$(BUILD_TYPE) build
	@echo ""
	@echo "ESP32 build completed successfully!"
	@echo "To flash: make flash-esp32"
	@echo "To monitor: make monitor-esp32"

# Hardware-specific targets (simplified)
flash erase reset debug:
	cmake --build $(BUILD_DIR) --target $@

# ESP32-specific hardware operations
flash-esp32:
	@echo "Flashing ESP32..."
	@python C:\Espressif\frameworks\esp-idf-v5.3.1\tools\idf.py flash

monitor-esp32:
	@echo "Starting ESP32 monitor..."
	@python C:\Espressif\frameworks\esp-idf-v5.3.1\tools\idf.py monitor

erase-esp32:
	@echo "Erasing ESP32 flash..."
	@python C:\Espressif\frameworks\esp-idf-v5.3.1\tools\idf.py erase-flash

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
	@echo "=================================="
	@echo "=== HW_API Build Configuration ==="
	@echo "=================================="
	@echo "Target Platform: $(TARGET_PLATFORM)"
ifeq ($(TARGET_PLATFORM),STM32)
	@echo "MCU Family: $(MCU_FAMILY)"
	@echo "MCU Specific: $(MCU_SPECIFIC)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
ifdef TOOLCHAIN_FILE
	@echo "Toolchain File: $(TOOLCHAIN_FILE)"
endif
ifdef STM32_HAL_PATH
	@echo "STM32 HAL Path: $(STM32_HAL_PATH)"
endif
	@echo "Available debug probes: st-link, jlink, openocd"
else ifeq ($(TARGET_PLATFORM),ESP32)
	@echo "MCU Family: $(MCU_FAMILY)"
	@echo "MCU Specific: $(MCU_SPECIFIC)"
	@echo "ESP32 IDF Target: $(ESP32_IDF_TARGET)"
	@echo "ESP32 IDF Path: $(ESP32_IDF_PATH)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
	@echo "Available debug probes: esptool, openocd"
else
	@echo "MCU Family: $(MCU_FAMILY)"
	@echo "MCU Specific: $(MCU_SPECIFIC)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
endif
	@echo "CMake Command: $(CMAKE_CMD)"
	@echo "=================================="

# Help target
help:
	@echo "HW_API Makefile - Hardware Abstraction Layer Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make [target] [TARGET_PLATFORM=STM32|ESP32] [BUILD_TYPE=Debug|Release]"
	@echo ""
	@echo "Build Targets:"
	@echo "  all              - Build for specified platform (default: STM32)"
	@echo "  stm32            - Build for STM32 platform"
	@echo "  esp32            - Build for ESP32 platform (requires: C:\Espressif\frameworks\esp-idf-v5.3.1\export.bat)"
	@echo "  clean            - Clean build directory"
	@echo "  prepare          - Prepare fresh build directory"
	@echo "  info             - Show current build configuration"
	@echo "  dependency       - Generate dependency graph"
	@echo ""
	@echo "STM32 Debug Probe Targets:"
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
	@echo "STM32 Examples:"
	@echo "  make stm32                             # Build STM32 with default settings"
	@echo "  make stm32 MCU_FAMILY=stm32c0xx        # Build for STM32C0xx family"
	@echo "  make stm32 MCU_FAMILY=stm32g0xx        # Build for STM32G0xx family"
	@echo ""
	@echo "ESP32 Examples:"
	@echo "  make esp32                             # Build for ESP32-C6 DevKitC-1 (default)"
	@echo "  make esp32 MCU_FAMILY=esp32c6          # Build for ESP32-C6 DevKitC-1"
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

