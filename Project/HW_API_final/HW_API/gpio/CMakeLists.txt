# GPIO module - Platform-specific GPIO implementations
set(GPIO_SOURCES gpio_test.cpp)

# Platform-specific source files
if(TARGET_PLATFORM STREQUAL "STM32")
    list(APPEND GPIO_SOURCES gpio_stm32.cpp)
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    list(APPEND GPIO_SOURCES gpio_esp32.cpp)
endif()

add_library(${HW_API_GPIO_LIBNAME} ${GPIO_SOURCES})

target_include_directories(${HW_API_GPIO_LIBNAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${CMAKE_CURRENT_SOURCE_DIR}/../platform
)

# Link with core library
target_link_libraries(${HW_API_GPIO_LIBNAME} PUBLIC ${HW_API_CORE_LIBNAME})

# Platform-specific configurations
if(TARGET_PLATFORM STREQUAL "STM32")
    target_compile_definitions(${HW_API_GPIO_LIBNAME} PUBLIC STM32_PLATFORM)
    target_link_libraries(${HW_API_GPIO_LIBNAME} PRIVATE ${HW_API_PLATFORM_LIBNAME})
    
    # Link STM32 HAL drivers (provides HAL functions for gpio_stm32.cpp)
    target_link_libraries(${HW_API_GPIO_LIBNAME} PRIVATE stm32_hal_wrapper)
    
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    target_compile_definitions(${HW_API_GPIO_LIBNAME} PUBLIC ESP32_PLATFORM)
    target_link_libraries(${HW_API_GPIO_LIBNAME} PRIVATE ${HW_API_PLATFORM_LIBNAME})
else()
    target_compile_definitions(${HW_API_GPIO_LIBNAME} PUBLIC TEST_PLATFORM)
endif()