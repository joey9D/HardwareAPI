set(CMSIS_DSP_LIBRARY "dsp")
set(CMSIS_NN_LIBRARY "nn")

add_library(cmsis STATIC
    Device/ST/STM32C0xx/Source/system_stm32c0xx.c
)

target_include_directories(cmsis
    PUBLIC
        Core/Include
        Device/ST/STM32C0xx/Include
)

# TODO: Check CubeMX which HSE_VALUE is used/needed.
# target_compile_definitions(cmsis
#     PRIVATE
#         HSE_VALUE=
# )

add_subdirectory(${CMSIS_DSP_LIBRARY})
add_subdirectory(${CMSIS_NN_LIBRARY})
