# ESP-IDF HW_API Component
# ChatGPT Empfehlung: idf_component_register() verwenden

# Sammle alle Quelldateien für ESP32
set(HW_API_SRCS
    # Core files
    "../../HW_API/core/core_test.cpp"
    
    # GPIO files  
    "../../HW_API/gpio/gpio_esp32.cpp"
    
    # SPI files
    "../../HW_API/spi/spi_esp32.cpp"
    
    # Platform files
    "../../HW_API/platform/esp32/esp32c6_devkitc/esp32c6_devkitc1_hw.cpp"
)

# Include Verzeichnisse
set(HW_API_INCLUDES
    "../../HW_API/core"
    "../../HW_API/gpio" 
    "../../HW_API/spi"
    "../../HW_API/platform"
    "../../HW_API/platform/esp32"
    "../../HW_API/platform/esp32/esp32c6_devkitc"
    "../../HW_API/drivers/esp32_hal_wrapper"
)

# ESP-IDF Komponente registrieren (ChatGPT Empfehlung)
idf_component_register(
    SRCS ${HW_API_SRCS}
    INCLUDE_DIRS ${HW_API_INCLUDES}
    REQUIRES driver esp_system esp_timer log
)

# ESP32-spezifische Compiler-Definitionen für ESP-IDF Component
target_compile_definitions(${COMPONENT_LIB} PUBLIC
    ESP32_PLATFORM=1
    ESP_PLATFORM=1
    ESP32C6=1
)

message(STATUS "HW_API ESP-IDF component registered successfully")
