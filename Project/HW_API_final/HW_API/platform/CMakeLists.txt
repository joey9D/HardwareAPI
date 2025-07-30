# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_platform)

message(STATUS "=== Configuring HW_API Platform Module (${TARGET_NAME}) ===")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific files (using centralized configuration)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring for STM32 platform...")
    
    # Use centrally configured STM32 variables from parent CMakeLists.txt
    message(STATUS "Using STM32 family: ${STM32_FAMILY}")
    message(STATUS "Using platform path: ${STM32_PLATFORM_PATH}")
    
    # Build file paths using central configuration
    set(FILTERED_SOURCES
        ${STM32_PLATFORM_PATH}/${STM32_HW_FILE}.cpp
    )
    
    set(FILTERED_HEADERS
        stm32/stm32x0_gpio_mapping.hpp
        ${STM32_PLATFORM_PATH}/${STM32_HW_FILE}.hpp
    )
       
    message(STATUS "Using STM32-specific platform files")

# ESP32 ...

else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in platform module: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Display files being used for this build
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Platform source files for ${TARGET_PLATFORM}:")
foreach(SOURCE_FILE ${FILTERED_SOURCES})
    message(STATUS "  - ${SOURCE_FILE}")
endforeach()

message(STATUS "Platform header files for ${TARGET_PLATFORM}:")
foreach(HEADER_FILE ${FILTERED_HEADERS})
    message(STATUS "  - ${HEADER_FILE}")
endforeach()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create the platform library
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
# Set include directories (minimal - main paths configured in parent CMakeLists.txt)
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

# Link with drivers module for HAL access (STM32 platform needs this)
if(TARGET_PLATFORM STREQUAL "STM32" AND TARGET hw_api_drivers)
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC hw_api_drivers)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE hw_api_drivers)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with hw_api_drivers for HAL access")
endif()

# Link with GPIO module (STM32 platform needs this)
if(TARGET_PLATFORM STREQUAL "STM32" AND TARGET hw_api_gpio)
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC hw_api_gpio)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE hw_api_gpio)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with hw_api_gpio for GPIO access")
endif()

message(STATUS "=== HW_API Platform Module Configuration Complete ===")
