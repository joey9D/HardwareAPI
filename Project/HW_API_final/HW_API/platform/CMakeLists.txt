# Platform-specific hardware implementations
# Only build the platform that is actually needed - ESP32 DISABLED
# if(TARGET_PLATFORM STREQUAL "ESP32")
#     add_subdirectory(esp32)
# endif()

if(TARGET_PLATFORM STREQUAL "STM32")
    add_subdirectory(stm32)
endif()

# Create a unified platform library
add_library(${HW_API_PLATFORM_LIBNAME} INTERFACE)

# Link platform-specific libraries based on target
if(TARGET_PLATFORM STREQUAL "STM32")
    target_link_libraries(${HW_API_PLATFORM_LIBNAME} INTERFACE stm32_hw)
# elseif(TARGET_PLATFORM STREQUAL "ESP32")
#     target_link_libraries(${HW_API_PLATFORM_LIBNAME} INTERFACE esp32_hw)
endif()

target_include_directories(${HW_API_PLATFORM_LIBNAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/esp32  # ESP32 DISABLED
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32
)