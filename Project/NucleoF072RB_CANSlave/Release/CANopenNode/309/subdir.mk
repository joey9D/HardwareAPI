################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/309/CO_gateway_ascii.c 

C_DEPS += \
./CANopenNode/309/CO_gateway_ascii.d 

OBJS += \
./CANopenNode/309/CO_gateway_ascii.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/309/%.o CANopenNode/309/%.su CANopenNode/309/%.cyclo: ../CANopenNode/309/%.c CANopenNode/309/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-309

clean-CANopenNode-2f-309:
	-$(RM) ./CANopenNode/309/CO_gateway_ascii.cyclo ./CANopenNode/309/CO_gateway_ascii.d ./CANopenNode/309/CO_gateway_ascii.o ./CANopenNode/309/CO_gateway_ascii.su

.PHONY: clean-CANopenNode-2f-309

