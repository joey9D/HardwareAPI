################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.cpp 

OBJS += \
./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.o 

CPP_DEPS += \
./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.d 


# Each subdirectory must supply rules for building sources it contributes
Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/%.o Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/%.su Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/%.cyclo: ../Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/%.cpp Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/Old" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/STM32G0_Hardware.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_driver_target.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_storageBlank.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Old_and_NewAbstraction-2f-Old-2f-Hardware_Abstraction-2f-STM32

clean-Old_and_NewAbstraction-2f-Old-2f-Hardware_Abstraction-2f-STM32:
	-$(RM) ./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.cyclo ./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.d ./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.o ./Old_and_NewAbstraction/Old/Hardware_Abstraction/STM32/STM32CANHardware.su

.PHONY: clean-Old_and_NewAbstraction-2f-Old-2f-Hardware_Abstraction-2f-STM32

