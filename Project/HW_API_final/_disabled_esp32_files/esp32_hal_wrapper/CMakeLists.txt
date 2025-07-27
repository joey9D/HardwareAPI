# ESP32 HAL Wrapper - Bridges HW_API to ESP-IDF
add_library(esp32_hal_wrapper
    esp32_hal_init.cpp
    esp32_hal_gpio.cpp
    esp32_hal_spi.cpp
)

target_include_directories(esp32_hal_wrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../core
)

# ESP-IDF integration
if(DEFINED IDF_PATH)
    # Include ESP-IDF components
    target_include_directories(esp32_hal_wrapper PRIVATE
        ${IDF_PATH}/components/driver/include
        ${IDF_PATH}/components/esp_timer/include
        ${IDF_PATH}/components/freertos/include
        ${IDF_PATH}/components/esp_common/include
        ${IDF_PATH}/components/hal/include
    )
    
    # Link ESP-IDF libraries (if building with ESP-IDF)
    if(ESP_PLATFORM)
        target_link_libraries(esp32_hal_wrapper PUBLIC
            idf::driver
            idf::esp_timer
            idf::freertos
        )
    endif()
else()
    message(WARNING "IDF_PATH not set. ESP32 HAL wrapper may not compile correctly.")
endif()

target_compile_definitions(esp32_hal_wrapper PUBLIC
    ESP32_PLATFORM
    ESP32_HAL_WRAPPER
)
