# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_spi)

message(STATUS "=======================================================")
message(STATUS "=== Configuring HW_API SPI Module (${TARGET_NAME}) ===")
message(STATUS "=======================================================")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific file filtering
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring for STM32 platform...")
    
    # Only include STM32-specific files for STM32 build
    set(FILTERED_SOURCES
        spi_stm32.cpp
        dma_stm32.cpp
    )
    
    set(FILTERED_HEADERS
        spi_interface.hpp
        spi_stm32.hpp
        dma_interface.hpp
        dma_stm32.hpp
    )
       
    message(STATUS "Using STM32-specific SPI files")

elseif(TARGET_PLATFORM STREQUAL "ESP32")
    message(STATUS "Configuring for ESP32 platform...")
    
    # Only include ESP32-specific files for ESP32 build
    set(FILTERED_SOURCES
        spi_esp32.cpp
    )
    
    set(FILTERED_HEADERS
        spi_interface.hpp
        spi_esp32.hpp
    )
       
    message(STATUS "Using ESP32-specific SPI files")

else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in spi module: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Display files being used for this build
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "SPI source files for ${TARGET_PLATFORM}:")
foreach(SOURCE_FILE ${FILTERED_SOURCES})
    message(STATUS "  - ${SOURCE_FILE}")
endforeach()

message(STATUS "SPI header files for ${TARGET_PLATFORM}:")
foreach(HEADER_FILE ${FILTERED_HEADERS})
    message(STATUS "  - ${HEADER_FILE}")
endforeach()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create the SPI library
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(FILTERED_SOURCES)
    # Create static library with source files
    add_library(${TARGET_NAME} STATIC 
        ${FILTERED_SOURCES}
        ${FILTERED_HEADERS}  # Include headers in target for IDE support
    )
    
    message(STATUS "Created ${TARGET_NAME} library with source files")
    
else()
    # Create interface library if no source files (header-only)
    add_library(${TARGET_NAME} INTERFACE)
    
    message(STATUS "Created ${TARGET_NAME} as header-only interface library")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set include directories
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(FILTERED_SOURCES)
    # For libraries with source files - use PUBLIC
    target_include_directories(${TARGET_NAME} 
        PUBLIC 
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    # For interface libraries - use INTERFACE
    target_include_directories(${TARGET_NAME} 
        INTERFACE 
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Link with required modules
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET hw_api_core)
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC hw_api_core)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE hw_api_core)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with hw_api_core")
endif()

# Link with drivers module for HAL access
if(TARGET_PLATFORM STREQUAL "STM32" AND TARGET hw_api_drivers)
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC hw_api_drivers)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE hw_api_drivers)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with hw_api_drivers for HAL access")
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32 will link with ESP32 drivers when implemented
    message(STATUS "ESP32 SPI drivers linking will be added in future implementation")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific compile definitions
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    target_compile_definitions(${TARGET_NAME} PUBLIC
        STM32_PLATFORM=1
    )
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    target_compile_definitions(${TARGET_NAME} PUBLIC
        ESP_PLATFORM=1
    )
else()
    message(WARNING "No platform-specific compile definitions for TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()

message(STATUS "=== HW_API SPI Module Configuration Complete ===")