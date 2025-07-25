# Core module - Hardware abstraction interfaces and base classes
add_library(${HW_API_CORE_LIBNAME} 
    core_test.cpp
)

target_include_directories(${HW_API_CORE_LIBNAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Platform-specific compile definitions
if(TARGET_PLATFORM STREQUAL "STM32")
    target_compile_definitions(${HW_API_CORE_LIBNAME} PUBLIC STM32_PLATFORM)
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    target_compile_definitions(${HW_API_CORE_LIBNAME} PUBLIC ESP32_PLATFORM)
else()
    target_compile_definitions(${HW_API_CORE_LIBNAME} PUBLIC TEST_PLATFORM)
endif()