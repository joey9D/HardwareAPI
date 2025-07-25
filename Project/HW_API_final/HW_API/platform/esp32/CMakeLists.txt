# ESP32 platform-specific hardware implementation
add_library(esp32_hw
    esp32c6_devkitc/esp32c6_hw.cpp
)

target_include_directories(esp32_hw PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/esp32c6_devkitc
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

# ESP32 specific compile definitions
target_compile_definitions(esp32_hw PUBLIC 
    ESP32_PLATFORM
    ESP32C6
)

# Link with ESP-IDF components if available
if(ESP_PLATFORM)
    # ESP-IDF specific linking
    target_link_libraries(esp32_hw PUBLIC 
        idf::driver
        idf::esp_timer
        idf::freertos
    )
endif()

# Create subdirectory targets for specific ESP32 variants
add_subdirectory(esp32c6_devkitc)