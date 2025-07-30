# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_app)

message(STATUS "=== Configuring Application (${TARGET_NAME}) ===")

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

message(STATUS "=== Application Configuration Complete ===")
