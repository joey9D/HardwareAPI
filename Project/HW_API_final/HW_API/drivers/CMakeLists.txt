# Define target name as variable for better maintainability
set(TARGET_NAME hw_api_drivers)

message(STATUS "=======================================================")
message(STATUS "=== Configuring HW_API Drivers Module (${TARGET_NAME}) ===")
message(STATUS "=======================================================")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Platform-specific driver configuration
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    message(STATUS "Configuring STM32 drivers...")
    
    # STM32 HAL dependency with FetchContent
    include(FetchContent)
    
    # Repository configuration comes from Makefile via CMake variables
    if(NOT DEFINED STM32_HAL_REPO)
        message(FATAL_ERROR "STM32_HAL_REPO not defined. Please build via Makefile: make stm32")
    endif()
    
    if(NOT DEFINED STM32_HAL_TAG)
        message(FATAL_ERROR "STM32_HAL_TAG not defined. Please build via Makefile: make stm32")
    endif()
    
    if(NOT DEFINED ARM_CMSIS_REPO)
        message(FATAL_ERROR "ARM_CMSIS_REPO not defined. Please build via Makefile: make stm32")
    endif()
    
    if(NOT DEFINED ARM_CMSIS_TAG)
        message(FATAL_ERROR "ARM_CMSIS_TAG not defined. Please build via Makefile: make stm32")
    endif()
    
    message(STATUS "STM32 HAL Repository: ${STM32_HAL_REPO}")
    message(STATUS "STM32 HAL Tag: ${STM32_HAL_TAG}")
    message(STATUS "STM32 CMSIS Repository: ${STM32_CMSIS_REPO}")
    message(STATUS "STM32 CMSIS Tag: ${STM32_CMSIS_TAG}")
    message(STATUS "ARM CMSIS Repository: ${ARM_CMSIS_REPO}")
    message(STATUS "ARM CMSIS Tag: ${ARM_CMSIS_TAG}")
    message(STATUS "HAL Prefix: ${HAL_PREFIX}")
    
    # Fetch STM32 HAL Driver
    FetchContent_Declare(
        stm32_hal
        GIT_REPOSITORY ${STM32_HAL_REPO}
        GIT_TAG        ${STM32_HAL_TAG}
        GIT_SHALLOW    TRUE
    )
    
    # Fetch STM32 CMSIS Device
    FetchContent_Declare(
        stm32_cmsis
        GIT_REPOSITORY ${STM32_CMSIS_REPO}
        GIT_TAG        ${STM32_CMSIS_TAG}
        GIT_SHALLOW    TRUE
    )
    
    # Fetch ARM CMSIS Core (needed for core_cm0plus.h)
    FetchContent_Declare(
        arm_cmsis_core
        GIT_REPOSITORY ${ARM_CMSIS_REPO}
        GIT_TAG        ${ARM_CMSIS_TAG}
        GIT_SHALLOW    TRUE
    )
    
    # Make content available
    FetchContent_MakeAvailable(stm32_hal stm32_cmsis arm_cmsis_core)
    
    message(STATUS "STM32 HAL Driver fetched to: ${stm32_hal_SOURCE_DIR}")
    message(STATUS "STM32 CMSIS Device fetched to: ${stm32_cmsis_SOURCE_DIR}")
    message(STATUS "ARM CMSIS Core fetched to: ${arm_cmsis_core_SOURCE_DIR}")
    
    # Debug: Check STM32_FAMILY variable
    message(STATUS "STM32_FAMILY in drivers: ${STM32_FAMILY}")
    
    # Family-specific configuration
    if(STM32_FAMILY STREQUAL "stm32c0xx")
        message(STATUS "Configuring for STM32C0xx family...")
        
        # HAL Wrapper sources for C0xx
        set(STM32_HAL_WRAPPER_SOURCES
            ${stm32_cmsis_SOURCE_DIR}/Source/Templates/gcc/startup_stm32c031xx.s
            stm32_hal_wrapper/common/syscalls.c
        )
        
        set(STM32_HAL_WRAPPER_HEADERS
            stm32_hal_wrapper/common/stm32_hal_inc.hpp
            stm32_hal_wrapper/stm32c0xx/stm32c0xx_hal_conf.h
        )
        
        # STM32C0xx HAL Core sources  
        set(STM32_HAL_CORE_SOURCES
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_cortex.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_dma.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_flash.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_gpio.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_pwr.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_rcc.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_spi.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_tim.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32c0xx_hal_uart.c
        )
        
        # STM32C0xx System sources (from CMSIS Device)
        set(STM32_SYSTEM_SOURCES
            ${stm32_cmsis_SOURCE_DIR}/Source/Templates/system_stm32c0xx.c
        )
        
    elseif(STM32_FAMILY STREQUAL "stm32g0xx")
        message(STATUS "Configuring for STM32G0xx family...")
        
        # HAL Wrapper sources for G0xx
        set(STM32_HAL_WRAPPER_SOURCES
            ${stm32_cmsis_SOURCE_DIR}/Source/Templates/gcc/startup_stm32g071xx.s
            stm32_hal_wrapper/common/syscalls.c
        )
        
        set(STM32_HAL_WRAPPER_HEADERS
            stm32_hal_wrapper/common/stm32_hal_inc.hpp
            stm32_hal_wrapper/stm32g0xx/stm32g0xx_hal_conf.h
        )
        
        # STM32G0xx HAL Core sources  
        set(STM32_HAL_CORE_SOURCES
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_cortex.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_dma.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_flash.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_gpio.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_pwr.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_pwr_ex.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_rcc.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_rcc_ex.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_spi.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_tim.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_tim_ex.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_uart.c
            ${stm32_hal_SOURCE_DIR}/Src/stm32g0xx_hal_uart_ex.c
        )
        
        # STM32G0xx System sources (from CMSIS Device)
        set(STM32_SYSTEM_SOURCES
            ${stm32_cmsis_SOURCE_DIR}/Source/Templates/system_stm32g0xx.c
        )
        
    else()
        message(FATAL_ERROR "Unsupported STM32_FAMILY: ${STM32_FAMILY}. Supported families: stm32c0xx, stm32g0xx")
    endif()

    # Create a separate HAL library to avoid include path issues
    add_library(stm32_hal_library STATIC 
        ${STM32_HAL_CORE_SOURCES}
        ${STM32_SYSTEM_SOURCES}
    )
    
    # Set family-specific include directories and compile definitions
    if(STM32_FAMILY STREQUAL "stm32c0xx")
        # Set include directories for C0xx HAL library compilation
        target_include_directories(stm32_hal_library 
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/common
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/stm32c0xx
                ${stm32_hal_SOURCE_DIR}/Inc
                ${stm32_cmsis_SOURCE_DIR}/Include
                ${arm_cmsis_core_SOURCE_DIR}/CMSIS/Core/Include
        )
        
        # Set compile definitions for C0xx HAL library
        target_compile_definitions(stm32_hal_library 
            PRIVATE
                USE_HAL_DRIVER
                STM32C0xx
                STM32C031xx
                STM32C031x6  # Device-specific define needed by CMSIS
                STM32_PLATFORM=1
        )
        
    elseif(STM32_FAMILY STREQUAL "stm32g0xx")
        # Set include directories for G0xx HAL library compilation
        target_include_directories(stm32_hal_library 
            PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/common
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/stm32g0xx
                ${stm32_hal_SOURCE_DIR}/Inc
                ${stm32_cmsis_SOURCE_DIR}/Include
                ${arm_cmsis_core_SOURCE_DIR}/CMSIS/Core/Include
        )
        
        # Set compile definitions for G0xx HAL library
        target_compile_definitions(stm32_hal_library 
            PRIVATE
                USE_HAL_DRIVER
                STM32G0xx
                STM32G071xx
                STM32G071xB  # Device-specific define needed by CMSIS
                STM32_PLATFORM=1
        )
    endif()
    
    # Combine wrapper sources only
    set(FILTERED_SOURCES
        ${STM32_HAL_WRAPPER_SOURCES}
    )
    
    set(FILTERED_HEADERS
        ${STM32_HAL_WRAPPER_HEADERS}
    )
    
    message(STATUS "Using STM32 HAL with wrapper")

else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM in drivers module: ${TARGET_PLATFORM}")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Display files being used for this build
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
message(STATUS "Driver source files for ${TARGET_PLATFORM}:")
foreach(SOURCE_FILE ${FILTERED_SOURCES})
    message(STATUS "  - ${SOURCE_FILE}")
endforeach()

message(STATUS "Driver header files for ${TARGET_PLATFORM}:")
foreach(HEADER_FILE ${FILTERED_HEADERS})
    message(STATUS "  - ${HEADER_FILE}")
endforeach()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Create the drivers library
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
if(TARGET_PLATFORM STREQUAL "STM32")
    # Set family-specific include directory
    if(STM32_FAMILY STREQUAL "stm32c0xx")
        set(STM32_FAMILY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/stm32c0xx)
    elseif(STM32_FAMILY STREQUAL "stm32g0xx")
        set(STM32_FAMILY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/stm32g0xx)
    else()
        message(FATAL_ERROR "Unsupported STM32_FAMILY for include directories: ${STM32_FAMILY}")
    endif()
    
    if(FILTERED_SOURCES)
        # For libraries with source files - use PUBLIC
        target_include_directories(${TARGET_NAME} 
            PUBLIC 
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/common
                ${STM32_FAMILY_INCLUDE_DIR}
                ${stm32_hal_SOURCE_DIR}/Inc
                ${stm32_cmsis_SOURCE_DIR}/Include
                ${arm_cmsis_core_SOURCE_DIR}/CMSIS/Core/Include
        )
    else()
        # For interface libraries - use INTERFACE
        target_include_directories(${TARGET_NAME} 
            INTERFACE 
                ${CMAKE_CURRENT_SOURCE_DIR}/stm32_hal_wrapper/common
                ${STM32_FAMILY_INCLUDE_DIR}
                ${stm32_hal_SOURCE_DIR}/Inc
                ${stm32_cmsis_SOURCE_DIR}/Include
                ${arm_cmsis_core_SOURCE_DIR}/CMSIS/Core/Include
        )
    endif()
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Link with core module and HAL library if available
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET hw_api_core)
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC hw_api_core stm32_hal_library)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE hw_api_core stm32_hal_library)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with hw_api_core and stm32_hal_library")
else()
    if(FILTERED_SOURCES)
        target_link_libraries(${TARGET_NAME} PUBLIC stm32_hal_library)
    else()
        target_link_libraries(${TARGET_NAME} INTERFACE stm32_hal_library)
    endif()
    message(STATUS "Linked ${TARGET_NAME} with stm32_hal_library")
endif()

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# STM32-specific compile definitions
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(TARGET_PLATFORM STREQUAL "STM32")
    if(FILTERED_SOURCES)
        target_compile_definitions(${TARGET_NAME} PUBLIC
            USE_HAL_DRIVER
            ${HAL_PREFIX}_HAL_DRIVER=1
        )
    else()
        target_compile_definitions(${TARGET_NAME} INTERFACE
            USE_HAL_DRIVER
            ${HAL_PREFIX}_HAL_DRIVER=1
        )
    endif()
    
    message(STATUS "Added STM32 HAL compile definitions: USE_HAL_DRIVER, ${HAL_PREFIX}_HAL_DRIVER")
endif()

message(STATUS "=== HW_API Drivers Module Configuration Complete ===")
