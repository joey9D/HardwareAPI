# ESP32C6 DevKitC specific implementation
add_library(esp32c6_devkitc_hw 
    esp32c6_hw.cpp
)

target_include_directories(esp32c6_devkitc_hw PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
)

target_compile_definitions(esp32c6_devkitc_hw PUBLIC 
    ESP32_PLATFORM
    ESP32C6
    ESP32C6_DEVKITC
)

# ESP-IDF specific linking if available
if(ESP_PLATFORM)
    target_link_libraries(esp32c6_devkitc_hw PUBLIC 
        idf::driver
        idf::esp_timer
        idf::freertos
    )
endif()

# Link with parent ESP32 library
target_link_libraries(esp32c6_devkitc_hw PUBLIC esp32_hw)
