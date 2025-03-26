################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/CANopen.c 

C_DEPS += \
./CANopenNode/CANopen.d 

OBJS += \
./CANopenNode/CANopen.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/%.o CANopenNode/%.su CANopenNode/%.cyclo: ../CANopenNode/%.c CANopenNode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode

clean-CANopenNode:
	-$(RM) ./CANopenNode/CANopen.cyclo ./CANopenNode/CANopen.d ./CANopenNode/CANopen.o ./CANopenNode/CANopen.su

.PHONY: clean-CANopenNode

