################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../app/CANopenMaster.cpp \
../app/CANopenNode.cpp \
../app/CiA417_CmdHandler.cpp \
../app/CiA417_Gateway.cpp \
../app/FunctionMapping.cpp \
../app/GPIOHandler.cpp \
../app/IOHandler.cpp \
../app/MainApp.cpp \
../app/NKET_Handler.cpp \
../app/NKET_Protokoll.cpp \
../app/NMT_LED.cpp \
../app/PDO_SDO.cpp \
../app/Trash.cpp \
../app/helper_functions.cpp 

OBJS += \
./app/CANopenMaster.o \
./app/CANopenNode.o \
./app/CiA417_CmdHandler.o \
./app/CiA417_Gateway.o \
./app/FunctionMapping.o \
./app/GPIOHandler.o \
./app/IOHandler.o \
./app/MainApp.o \
./app/NKET_Handler.o \
./app/NKET_Protokoll.o \
./app/NMT_LED.o \
./app/PDO_SDO.o \
./app/Trash.o \
./app/helper_functions.o 

CPP_DEPS += \
./app/CANopenMaster.d \
./app/CANopenNode.d \
./app/CiA417_CmdHandler.d \
./app/CiA417_Gateway.d \
./app/FunctionMapping.d \
./app/GPIOHandler.d \
./app/IOHandler.d \
./app/MainApp.d \
./app/NKET_Handler.d \
./app/NKET_Protokoll.d \
./app/NMT_LED.d \
./app/PDO_SDO.d \
./app/Trash.d \
./app/helper_functions.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.cpp app/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/Old" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/STM32G0_Hardware.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_driver_target.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common/CO_storageBlank.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/CANopenMaster.cyclo ./app/CANopenMaster.d ./app/CANopenMaster.o ./app/CANopenMaster.su ./app/CANopenNode.cyclo ./app/CANopenNode.d ./app/CANopenNode.o ./app/CANopenNode.su ./app/CiA417_CmdHandler.cyclo ./app/CiA417_CmdHandler.d ./app/CiA417_CmdHandler.o ./app/CiA417_CmdHandler.su ./app/CiA417_Gateway.cyclo ./app/CiA417_Gateway.d ./app/CiA417_Gateway.o ./app/CiA417_Gateway.su ./app/FunctionMapping.cyclo ./app/FunctionMapping.d ./app/FunctionMapping.o ./app/FunctionMapping.su ./app/GPIOHandler.cyclo ./app/GPIOHandler.d ./app/GPIOHandler.o ./app/GPIOHandler.su ./app/IOHandler.cyclo ./app/IOHandler.d ./app/IOHandler.o ./app/IOHandler.su ./app/MainApp.cyclo ./app/MainApp.d ./app/MainApp.o ./app/MainApp.su ./app/NKET_Handler.cyclo ./app/NKET_Handler.d ./app/NKET_Handler.o ./app/NKET_Handler.su ./app/NKET_Protokoll.cyclo ./app/NKET_Protokoll.d ./app/NKET_Protokoll.o ./app/NKET_Protokoll.su ./app/NMT_LED.cyclo ./app/NMT_LED.d ./app/NMT_LED.o ./app/NMT_LED.su ./app/PDO_SDO.cyclo ./app/PDO_SDO.d ./app/PDO_SDO.o ./app/PDO_SDO.su ./app/Trash.cyclo ./app/Trash.d ./app/Trash.o ./app/Trash.su ./app/helper_functions.cyclo ./app/helper_functions.d ./app/helper_functions.o ./app/helper_functions.su

.PHONY: clean-app

