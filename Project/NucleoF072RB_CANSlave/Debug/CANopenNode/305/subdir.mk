################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/305/CO_LSSmaster.c \
../CANopenNode/305/CO_LSSslave.c 

C_DEPS += \
./CANopenNode/305/CO_LSSmaster.d \
./CANopenNode/305/CO_LSSslave.d 

OBJS += \
./CANopenNode/305/CO_LSSmaster.o \
./CANopenNode/305/CO_LSSslave.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/305/%.o CANopenNode/305/%.su CANopenNode/305/%.cyclo: ../CANopenNode/305/%.c CANopenNode/305/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -DSTM32F0 -c -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/NucleoF072RB_CANSlave/Core/Inc" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-305

clean-CANopenNode-2f-305:
	-$(RM) ./CANopenNode/305/CO_LSSmaster.cyclo ./CANopenNode/305/CO_LSSmaster.d ./CANopenNode/305/CO_LSSmaster.o ./CANopenNode/305/CO_LSSmaster.su ./CANopenNode/305/CO_LSSslave.cyclo ./CANopenNode/305/CO_LSSslave.d ./CANopenNode/305/CO_LSSslave.o ./CANopenNode/305/CO_LSSslave.su

.PHONY: clean-CANopenNode-2f-305

