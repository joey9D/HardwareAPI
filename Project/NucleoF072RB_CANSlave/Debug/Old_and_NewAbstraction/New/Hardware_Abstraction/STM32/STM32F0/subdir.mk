################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.cpp \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.cpp 

OBJS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.o \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.o 

CPP_DEPS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.d \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.d 


# Each subdirectory must supply rules for building sources it contributes
Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.o Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.su Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.cyclo: ../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.cpp Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -DSTM32F0 -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/app" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/basic" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0

clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0:
	-$(RM) ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.su ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.su

.PHONY: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0

