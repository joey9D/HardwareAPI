################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CANopenNodeInterface/CANOpenManager.cpp \
../CANopenNodeInterface/CanNode.cpp \
../CANopenNodeInterface/CanStackInterface.cpp 

C_SRCS += \
../CANopenNodeInterface/OD.c 

C_DEPS += \
./CANopenNodeInterface/OD.d 

OBJS += \
./CANopenNodeInterface/CANOpenManager.o \
./CANopenNodeInterface/CanNode.o \
./CANopenNodeInterface/CanStackInterface.o \
./CANopenNodeInterface/OD.o 

CPP_DEPS += \
./CANopenNodeInterface/CANOpenManager.d \
./CANopenNodeInterface/CanNode.d \
./CANopenNodeInterface/CanStackInterface.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNodeInterface/%.o CANopenNodeInterface/%.su CANopenNodeInterface/%.cyclo: ../CANopenNodeInterface/%.cpp CANopenNodeInterface/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/Old" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/STM32G0_Hardware.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_driver_target.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_storageBlank.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CANopenNodeInterface/%.o CANopenNodeInterface/%.su CANopenNodeInterface/%.cyclo: ../CANopenNodeInterface/%.c CANopenNodeInterface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Drivers/STM32G0xx_HAL_Driver/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/Updated_IO/HeaderFiles" -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/Boards" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNodeInterface

clean-CANopenNodeInterface:
	-$(RM) ./CANopenNodeInterface/CANOpenManager.cyclo ./CANopenNodeInterface/CANOpenManager.d ./CANopenNodeInterface/CANOpenManager.o ./CANopenNodeInterface/CANOpenManager.su ./CANopenNodeInterface/CanNode.cyclo ./CANopenNodeInterface/CanNode.d ./CANopenNodeInterface/CanNode.o ./CANopenNodeInterface/CanNode.su ./CANopenNodeInterface/CanStackInterface.cyclo ./CANopenNodeInterface/CanStackInterface.d ./CANopenNodeInterface/CanStackInterface.o ./CANopenNodeInterface/CanStackInterface.su ./CANopenNodeInterface/OD.cyclo ./CANopenNodeInterface/OD.d ./CANopenNodeInterface/OD.o ./CANopenNodeInterface/OD.su

.PHONY: clean-CANopenNodeInterface

