################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/303/CO_LEDs.c 

C_DEPS += \
./CANopenNode/303/CO_LEDs.d 

OBJS += \
./CANopenNode/303/CO_LEDs.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/303/%.o CANopenNode/303/%.su CANopenNode/303/%.cyclo: ../CANopenNode/303/%.c CANopenNode/303/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -DSTM32F0 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/NucleoF072RB_CANSlave/Core/Inc" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-303

clean-CANopenNode-2f-303:
	-$(RM) ./CANopenNode/303/CO_LEDs.cyclo ./CANopenNode/303/CO_LEDs.d ./CANopenNode/303/CO_LEDs.o ./CANopenNode/303/CO_LEDs.su

.PHONY: clean-CANopenNode-2f-303

