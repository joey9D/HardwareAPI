################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hardware_Abstraction/STM32/old/oldstm32.cpp 

OBJS += \
./Hardware_Abstraction/STM32/old/oldstm32.o 

CPP_DEPS += \
./Hardware_Abstraction/STM32/old/oldstm32.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware_Abstraction/STM32/old/%.o Hardware_Abstraction/STM32/old/%.su Hardware_Abstraction/STM32/old/%.cyclo: ../Hardware_Abstraction/STM32/old/%.cpp Hardware_Abstraction/STM32/old/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/Test/NucleoF072RB_CANSlave/Hardware_Abstraction" -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/Test/NucleoF072RB_CANSlave/Hardware_Abstraction/STM32/STM32CANHardware.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/Hardware_Abstraction/CANHardwareFactory.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/app/FunctionMapping.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/Hardware_Abstraction/CANHardwareInterface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/Hardware_Abstraction/CANHardwareInterface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/CANopenNodeInterface/CiA417_LiftTypes.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Erste-Projekt/30-CAN_Stack/NucleoF072RB_CANSlave/CANopenNodeInterface/CiA417_VirtualIOMapping.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Hardware_Abstraction-2f-STM32-2f-old

clean-Hardware_Abstraction-2f-STM32-2f-old:
	-$(RM) ./Hardware_Abstraction/STM32/old/oldstm32.cyclo ./Hardware_Abstraction/STM32/old/oldstm32.d ./Hardware_Abstraction/STM32/old/oldstm32.o ./Hardware_Abstraction/STM32/old/oldstm32.su

.PHONY: clean-Hardware_Abstraction-2f-STM32-2f-old

