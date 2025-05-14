add_executable(${EXECUTABLE_NAME} "main.cpp")

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    "./"
)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${BASIC_LIBRARY}
    ${GPIO_LIBRARY}
    ${CORE_LIBRARY}
    ${MCU_DRIVERS_LIBRARY}
)

####################################
# CONFIGURE TARGET #
####################################
target_sources(cmsis PRIVATE ../${MCU_DRIVERS_LIBRARY}/CMSIS/Device/ST/STM32C0xx/Source/startup_stm32c031xx.s)

target_link_options(${EXECUTABLE_NAME} PRIVATE
    -mcpu=cortex-m0plus
#    -mfloat-abi=hard
#    -mfpu=fpv4-sp-d16
    -Wl,--gc-sections
    -specs=nano.specs
    -specs=nosys.specs
    -Wl,-Map=${EXECUTABLE_NAME}.map,--cref
    -T${CMAKE_CURRENT_SOURCE_DIR}/../${MCU_DRIVERS_LIBRARY}/CMSIS/Device/ST/STM32C0xx/Source/linker/STM32C031C6TX_FLASH.ld
)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES SUFFIX ".elf")
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} ${EXECUTABLE_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE_NAME}.elf "${EXECUTABLE_NAME}.bin"
)
