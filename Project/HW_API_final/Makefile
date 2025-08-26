
# HW_API Build System

# Platform detection: Load appropriate configuration
# Default to STM32 if no platform specified
# TARGET_PLATFORM ?= ESP32

# ifeq ($(TARGET_PLATFORM),ESP32)
    include config/esp32_config.mk  # ESP32-specific configuration  
# else
#     include config/stm32_config.mk  # STM32-specific configuration (default)
# endif


# Base CMake command (platform-specific configuration added in build targets)
CMAKE_CMD = cmake -S . -B $(BUILD_DIR) -G "Ninja" -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTARGET_PLATFORM=$(TARGET_PLATFORM)

# Default target
.PHONY: all clean prepare stm32 esp32 info help flash erase reset debug stm32-flash esp32-flash stm32-erase esp32-erase stm32-reset esp32-reset stm32-debug esp32-debug esp32-debug-gdb esp32-debug-tui esp32-monitor

all: info
	@mkdir -p $(BUILD_DIR)
	$(CMAKE_CMD)
	cmake --build $(BUILD_DIR) -j

# Platform-specific builds
stm32-build:
	@echo "================================================================================"
	@echo "=== Building STM32 Platform ==="
	@echo "================================================================================"
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
# ESP32 Build with ESP-IDF via CMake 
esp32: TARGET_PLATFORM=ESP32
esp32-build:
	@echo "================================================================================"
	@echo "=== Building ESP32 Platform (ESP-IDF) ==="
	@echo "================================================================================"
	@echo "Setting up ESP32 build environment..."
	@echo "IDF Target: $(IDF_TARGET)"
	@echo "Board: $(BOARD)"
	
	# Ensure ESP-IDF environment is sourced
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Bitte export.bat im Terminal ausführen!"; \
		exit 1; \
	fi
	
	# Create build directory
	@mkdir -p "$(BUILD_DIR)"
	
	# Configure ESP32 build via CMake (using ESP-IDF standard parameters)
	@echo "Configuring ESP32 build..."
	@cd "$(BUILD_DIR)" && cmake .. -G "Ninja" \
		-DESP_PLATFORM=1 \
		-DIDF_TARGET=$(IDF_TARGET) \
		-DBOARD=$(BOARD) \
		-DDEBUG_PROBE=$(DEBUG_PROBE) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	
	# Build the project
	@echo "Building ESP32 project..."
	@cd "$(BUILD_DIR)" && cmake --build . -j
	
	@echo ""
	@echo "ESP32 build completed successfully!"
	@echo "Firmware location: $(BUILD_DIR)"
	@echo "To flash: make esp32-flash"
	@echo "To debug: make esp32-debug"
	@echo "To monitor: make esp32-monitor"
	@echo ""
	@echo "IMPORTANT: For debugging, ensure ESP-IDF environment is loaded:"
	@echo "  Run: $(ESP32_EXPORT_BAT)"
	@echo "  Then restart your terminal before running debug commands"

# Hardware-specific targets (platform-specific)
stm32-flash:
	cmake --build build --target flash

esp32-flash:
	@echo "Flashing ESP32..."
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Please run: $(ESP32_EXPORT_BAT)"; \
		exit 1; \
	fi
	@python "$$IDF_PATH/tools/idf.py" -B $(BUILD_DIR) -p $(ESP32_PORT) -b $(ESP32_BAUD) flash

stm32-erase:
	cmake --build build --target erase

esp32-erase:
	@echo "Erasing ESP32 flash..."
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Please run: $(ESP32_EXPORT_BAT)"; \
		exit 1; \
	fi
	@python "$$IDF_PATH/tools/idf.py" -B $(BUILD_DIR) -p $(ESP32_PORT) -b $(ESP32_BAUD) erase-flash

stm32-reset:
	cmake --build build --target reset

esp32-reset:
	@echo "Resetting ESP32..."
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Please run: $(ESP32_EXPORT_BAT)"; \
		exit 1; \
	fi
	@python "$$IDF_PATH/tools/idf.py" -B $(BUILD_DIR) -p $(ESP32_PORT) app-flash

stm32-debug:
	cmake --build build --target debug

esp32-debug:
	@echo "Starting ESP32 debugging session ..."
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Please set IDF_PATH environment variable."; \
		exit 1; \
	fi
	@python "$$IDF_PATH/tools/idf.py" -B $(BUILD_DIR) -p $(ESP32_PORT) openocd gdb



esp32-monitor:
	@echo "Starting ESP32 serial monitor only..."
	@if [ -z "$$IDF_PATH" ]; then \
		echo "Error: ESP-IDF environment not found. Please run: $(ESP32_EXPORT_BAT)"; \
		exit 1; \
	fi
	@python "$$IDF_PATH/tools/idf.py" -B $(BUILD_DIR) -p $(ESP32_PORT) monitor

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
	@echo "================================================================================"
	@echo "=== HW_API Build Configuration ==="
	@echo "================================================================================"
	@echo "Target Platform: $(TARGET_PLATFORM)"
ifeq ($(TARGET_PLATFORM),STM32)
	@echo "MCU Family: $(MCU_FAMILY)"
	@echo "MCU Specific: $(MCU_SPECIFIC)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
endif
ifeq ($(TARGET_PLATFORM),ESP32)
	@echo "ESP32 IDF Target: $(IDF_TARGET)"
	@echo "Board: $(BOARD)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Build Directory: $(BUILD_DIR)"
	@echo "Debug Probe: $(DEBUG_PROBE)"
endif
	@echo "================================================================================"
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
	@echo "Hardware Operations (platform-aware):"
	@echo "  flash            - Flash firmware to target (auto-detects platform)"
	@echo "  erase            - Erase target flash (auto-detects platform)" 
	@echo "  reset            - Reset target device (auto-detects platform)"
	@echo "  debug            - Start debug session/monitor (auto-detects platform)"
	@echo ""
	@echo "Hardware Operations (platform-specific):"
	@echo "  stm32-flash      - Flash STM32 firmware"
	@echo "  esp32-flash      - Flash ESP32 firmware"
	@echo "  stm32-erase      - Erase STM32 flash"
	@echo "  esp32-erase      - Erase ESP32 flash"
	@echo "  stm32-reset      - Reset STM32 device"
	@echo "  esp32-reset      - Reset ESP32 device"
	@echo "  stm32-debug      - Start STM32 debug session"
	@echo "  esp32-debug      - Start ESP32 step-by-step debugging (USB-JTAG)"
	@echo "  esp32-monitor    - Start ESP32 serial monitor only"
	@echo ""
	@echo "Platform Usage:"
	@echo "  STM32: Use 'make stm32' first, then 'make stm32-flash'"
	@echo "  ESP32: Use 'make esp32' first, then 'make esp32-flash'"
	@echo ""
	@echo "STM32 Examples:"
	@echo "  make stm32                             # Build STM32 with default settings"
	@echo "  make stm32 MCU_FAMILY=stm32c0xx        # Build for STM32C0xx family"
	@echo "  make stm32 MCU_FAMILY=stm32g0xx        # Build for STM32G0xx family"
	@echo ""
	@echo "ESP32 Examples:"
	@echo "  make esp32                             # Build for ESP32-C6 DevKitC-1 (default)"
	@echo "  make esp32 IDF_TARGET=esp32c6          # Build for ESP32-C6 DevKitC-1"
	@echo "  make esp32 IDF_TARGET=esp32c3          # Build for ESP32-C3"
	@echo "  make esp32 IDF_TARGET=esp32            # Build for ESP32 original"
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

