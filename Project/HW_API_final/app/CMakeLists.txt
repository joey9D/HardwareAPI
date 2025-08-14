# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_app)

message(STATUS "=======================================================")
message(STATUS "=== Configuring Application (${TARGET_NAME}) ===")
message(STATUS "=======================================================")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Application source files
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
set(APP_SOURCES
    main.cpp
)

# Platform-specific interrupt handlers (force direct linking to override weak symbols)
if(TARGET_PLATFORM STREQUAL "STM32")
    # Family-specific interrupt handlers
    if(MCU_FAMILY STREQUAL "stm32c0xx")
        list(APPEND APP_SOURCES
            ../HW_API/platform/stm32/stm32c0xx/stm32c0xx_it.c
        )
        message(STATUS "Added STM32C0xx interrupt handlers directly to application")
    elseif(MCU_FAMILY STREQUAL "stm32g0xx")
        list(APPEND APP_SOURCES
            ../HW_API/platform/stm32/stm32g0xx/stm32g0xx_it.c
        )
        message(STATUS "Added STM32G0xx interrupt handlers directly to application")
    else()
        message(FATAL_ERROR "Unsupported MCU_FAMILY for interrupt handlers: ${MCU_FAMILY}")
    endif()
endif()

set(APP_HEADERS
    main.hpp
)

message(STATUS "Application source files:")
foreach(SOURCE_FILE ${APP_SOURCES})
    message(STATUS "  - ${SOURCE_FILE}")
endforeach()

message(STATUS "Application header files:")
foreach(HEADER_FILE ${APP_HEADERS})
    message(STATUS "  - ${HEADER_FILE}")
endforeach()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create the application executable
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
add_executable(${TARGET_NAME} 
    ${APP_SOURCES}
    ${APP_HEADERS}  # Include headers in target for IDE support
)

# Set output name without prefix
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "main")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Add STM32-specific compile definitions to the app target
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    # Common STM32 definitions
    target_compile_definitions(${TARGET_NAME} PRIVATE
        STM32_PLATFORM=1
        STM32_FAMILY_${MCU_FAMILY}=1
        USE_HAL_DRIVER=1
        DEBUG=1
    )
    
    # Family-specific compile definitions and linker script
    if(MCU_FAMILY STREQUAL "stm32c0xx")
        target_compile_definitions(${TARGET_NAME} PRIVATE
            STM32C0xx=1
            STM32C031xx=1
            STM32C031x6=1
        )
        set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../HW_API/platform/stm32/stm32c0xx/STM32C031C6Tx_FLASH.ld")
        message(STATUS "Using STM32C031C6 linker script")
        
    elseif(MCU_FAMILY STREQUAL "stm32g0xx")
        target_compile_definitions(${TARGET_NAME} PRIVATE
            STM32G0xx=1
            STM32G071xx=1
            STM32G071xB=1
        )
        set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../HW_API/platform/stm32/stm32g0xx/STM32G071RBTx_FLASH.ld")
        message(STATUS "Using STM32G071RB linker script")
        
    else()
        message(FATAL_ERROR "Unsupported MCU_FAMILY for compile definitions: ${MCU_FAMILY}")
    endif()
    
    # Apply linker script
    target_link_options(${TARGET_NAME} PRIVATE 
        -T${LINKER_SCRIPT}
        -Wl,--print-memory-usage
    )
    
    message(STATUS "Added STM32 compile definitions to ${TARGET_NAME}")
    message(STATUS "Using linker script: ${LINKER_SCRIPT}")
endif()

message(STATUS "Created ${TARGET_NAME} executable")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Link with HW_API modules
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    # STM32 needs the HAL drivers library
    target_link_libraries(${TARGET_NAME} PRIVATE
        hw_api_core
        hw_api_gpio
        hw_api_spi
        hw_api_drivers
        hw_api_platform
    )
    message(STATUS "Linked ${TARGET_NAME} with STM32 HW_API modules (including drivers and SPI)")
elseif(TARGET_PLATFORM STREQUAL "ESP32")
    # ESP32 doesn't need hw_api_drivers (uses ESP-IDF instead)
    target_link_libraries(${TARGET_NAME} PRIVATE
        hw_api_core
        hw_api_gpio
        hw_api_spi
        hw_api_platform
    )
    message(STATUS "Linked ${TARGET_NAME} with ESP32 HW_API modules (no drivers needed)")
else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set include directories
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Generate binary file for flashing (STM32 only)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    # Create .bin file from the ELF executable
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_NAME}> ${CMAKE_PROJECT_NAME}.bin
        COMMENT "Creating binary file for flashing: ${CMAKE_PROJECT_NAME}.bin"
    )
    
    # Copy .bin file to build root for easier flashing
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_PROJECT_NAME}.bin ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
        COMMENT "Copying ${CMAKE_PROJECT_NAME}.bin to build directory"
    )
    
    message(STATUS "Will generate ${CMAKE_PROJECT_NAME}.bin for flashing")
endif()

message(STATUS "=== Application Configuration Complete ===")
