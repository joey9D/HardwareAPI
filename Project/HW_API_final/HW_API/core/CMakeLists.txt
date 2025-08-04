# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_core)

message(STATUS "=======================================================")
message(STATUS "=== Configuring HW_API Core Module (${TARGET_NAME}) ===")
message(STATUS "=======================================================")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific files
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring for STM32 platform...")
    
    # Remove ESP32-specific files for STM32 build
    set(FILTERED_SOURCES
        # core_test.cpp
    )
    
    set(FILTERED_HEADERS
        # core_test.hpp
        hw_enum_classes.hpp
        hw_enum_stm32.hpp
        hw_factory.hpp
        hw_interface.hpp
        
        # make pin_config is included
        pin_config.hpp

        timer.hpp
    )

    message(STATUS "Using ${TARGET_PLATFORM}-specific core files")

elseif(TARGET_PLATFORM STREQUAL "ESP32")
    message(STATUS "Configuring for ESP32 platform...")

    # ESP32-specific core files
    set(FILTERED_SOURCES
        # core_test.cpp
    )
    
    set(FILTERED_HEADERS
        # core_test.hpp
        hw_enum_classes.hpp
        hw_enum_esp32.hpp
        hw_factory.hpp
        hw_interface.hpp
        
        # make pin_config is included
        pin_config.hpp

        timer.hpp
    )

    message(STATUS "Using ESP32-specific core files")

else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in core module: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Display files being used for this build
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Core source files for ${TARGET_PLATFORM}:")
foreach(SOURCE_FILE ${FILTERED_SOURCES})
    message(STATUS "  - ${SOURCE_FILE}")
endforeach()

message(STATUS "Core header files for ${TARGET_PLATFORM}:")
foreach(HEADER_FILE ${FILTERED_HEADERS})
    message(STATUS "  - ${HEADER_FILE}")
endforeach()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create the core library
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
            ${CMAKE_CURRENT_SOURCE_DIR}/..  # Parent HW_API directory
    )
else()
    # For interface libraries - use INTERFACE
    target_include_directories(${TARGET_NAME} 
        INTERFACE 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/..  # Parent HW_API directory
    )
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific compile definitions
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    if(FILTERED_SOURCES)
        target_compile_definitions(${TARGET_NAME} PUBLIC
            STM32_PLATFORM=1
            # HW_CORE_STM32=1
        )
        # Add STM32 family-specific definitions
        if(MCU_FAMILY STREQUAL "stm32c0xx")
            target_compile_definitions(${TARGET_NAME} PUBLIC STM32C0xx=1)
        elseif(MCU_FAMILY STREQUAL "stm32g0xx")
            target_compile_definitions(${TARGET_NAME} PUBLIC STM32G0xx=1)
        endif()
    else()
        target_compile_definitions(${TARGET_NAME} INTERFACE
            STM32_PLATFORM=1
            # HW_CORE_STM32=1
        )
        # Add STM32 family-specific definitions
        if(MCU_FAMILY STREQUAL "stm32c0xx")
            target_compile_definitions(${TARGET_NAME} INTERFACE STM32C0xx=1)
        elseif(MCU_FAMILY STREQUAL "stm32g0xx")
            target_compile_definitions(${TARGET_NAME} INTERFACE STM32G0xx=1)
        endif()
    endif()
    
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    if(FILTERED_SOURCES)
        target_compile_definitions(${TARGET_NAME} PUBLIC
            ESP32_PLATFORM=1
        )
        # Add ESP32 family-specific definitions
        if(ESP32_FAMILY STREQUAL "esp32c6")
            target_compile_definitions(${TARGET_NAME} PUBLIC ESP32C6=1)
        endif()
    else()
        target_compile_definitions(${TARGET_NAME} INTERFACE
            ESP32_PLATFORM=1
        )
        # Add ESP32 family-specific definitions
        if(ESP32_FAMILY STREQUAL "esp32c6")
            target_compile_definitions(${TARGET_NAME} INTERFACE ESP32C6=1)
        endif()
    endif()
    
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in core module: ${TARGET_PLATFORM}")
endif()
