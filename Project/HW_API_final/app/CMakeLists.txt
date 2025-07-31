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
    target_compile_definitions(${TARGET_NAME} PRIVATE
        STM32_PLATFORM=1
        STM32_FAMILY_${STM32_FAMILY}=1
        STM32C0xx=1
        STM32C031xx=1
        STM32C031x6=1
        USE_HAL_DRIVER=1
        DEBUG=1
    )
    message(STATUS "Added STM32 compile definitions to ${TARGET_NAME}")
endif()

message(STATUS "Created ${TARGET_NAME} executable")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Link with HW_API modules
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
target_link_libraries(${TARGET_NAME} PRIVATE
    hw_api_core
    hw_api_gpio
    hw_api_platform
    hw_api_drivers
)

message(STATUS "Linked ${TARGET_NAME} with HW_API modules")

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
