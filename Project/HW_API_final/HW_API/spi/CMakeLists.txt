# SPI module - Platform-specific SPI implementations
set(SPI_SOURCES spi_test.cpp)

# Add platform-specific SPI sources when they exist
# if(TARGET_PLATFORM STREQUAL "STM32")
#     list(APPEND SPI_SOURCES spi_stm32.cpp)
# elseif(TARGET_PLATFORM STREQUAL "ESP32")
#     list(APPEND SPI_SOURCES spi_esp32.cpp)
# endif()

add_library(${HW_API_SPI_LIBNAME} ${SPI_SOURCES})

target_include_directories(${HW_API_SPI_LIBNAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${CMAKE_CURRENT_SOURCE_DIR}/../platform
)

# Link with core library
target_link_libraries(${HW_API_SPI_LIBNAME} PUBLIC ${HW_API_CORE_LIBNAME})

# Platform-specific configurations
if(TARGET_PLATFORM STREQUAL "STM32")
    target_compile_definitions(${HW_API_SPI_LIBNAME} PUBLIC STM32_PLATFORM)
    target_link_libraries(${HW_API_SPI_LIBNAME} PRIVATE ${HW_API_PLATFORM_LIBNAME})
# elseif(TARGET_PLATFORM STREQUAL "ESP32")
#     target_compile_definitions(${HW_API_SPI_LIBNAME} PUBLIC ESP32_PLATFORM)
#     target_link_libraries(${HW_API_SPI_LIBNAME} PRIVATE ${HW_API_PLATFORM_LIBNAME})
else()
    target_compile_definitions(${HW_API_SPI_LIBNAME} PUBLIC TEST_PLATFORM)
endif()