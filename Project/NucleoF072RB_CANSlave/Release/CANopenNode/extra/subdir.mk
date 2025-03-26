################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/extra/CO_trace.c 

C_DEPS += \
./CANopenNode/extra/CO_trace.d 

OBJS += \
./CANopenNode/extra/CO_trace.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/extra/%.o CANopenNode/extra/%.su CANopenNode/extra/%.cyclo: ../CANopenNode/extra/%.c CANopenNode/extra/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-extra

clean-CANopenNode-2f-extra:
	-$(RM) ./CANopenNode/extra/CO_trace.cyclo ./CANopenNode/extra/CO_trace.d ./CANopenNode/extra/CO_trace.o ./CANopenNode/extra/CO_trace.su

.PHONY: clean-CANopenNode-2f-extra

