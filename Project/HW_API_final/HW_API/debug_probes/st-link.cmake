add_custom_target(flash
    COMMAND STM32_Programmer_CLI --connect port=SWD --write ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin 0x08000000 --verify -rst
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(erase
    COMMAND STM32_Programmer_CLI --connect port=SWD --erase all
    USES_TERMINAL
)

add_custom_target(reset
    COMMAND STM32_Programmer_CLI --connect port=SWD -rst
    USES_TERMINAL
)

find_program(STM32_Programmer_CLI NAMES STM32_Programmer_CLI)
if(STM32_Programmer_CLI)
    get_filename_component(STM32_Programmer_CLI_DIRNAME ${STM32_Programmer_CLI} DIRECTORY)
    add_custom_target(debug DEPENDS flash
        COMMAND ST-LINK_gdbserver --swd --verbose --persistent --verify --port-number 2331
            --stm32cubeprogrammer-path ${STM32_Programmer_CLI_DIRNAME}
        USES_TERMINAL
    )
else()
    message(WARNING "STM32_Programmer_CLI not found. Debug target will not be available.")
    add_custom_target(debug
        COMMAND ${CMAKE_COMMAND} -E echo "STM32CubeProgrammer not found. Please install STM32CubeCLT."
        USES_TERMINAL
    )
endif()
