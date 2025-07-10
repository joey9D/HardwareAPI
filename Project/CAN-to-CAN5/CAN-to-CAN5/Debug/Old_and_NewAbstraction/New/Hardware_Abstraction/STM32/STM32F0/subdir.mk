################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.cpp \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.cpp \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.cpp \
../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.cpp 

OBJS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.o \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.o \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.o \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.o 

CPP_DEPS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.d \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.d \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.d \
./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.d 


# Each subdirectory must supply rules for building sources it contributes
Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.o Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.su Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.cyclo: ../Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/%.cpp Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/Old" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/STM32G0_Hardware.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_driver_target.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_storageBlank.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0

clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0:
	-$(RM) ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/Hardware_Definitions.su ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.su ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Pins_config.su ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/ShiftRegisterIO.su

.PHONY: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-STM32-2f-STM32F0

