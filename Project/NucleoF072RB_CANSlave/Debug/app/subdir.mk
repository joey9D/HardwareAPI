################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../app/CANopenNode.cpp \
../app/CiA417_CmdHandler.cpp \
../app/CiA417_Gateway.cpp \
../app/FunctionMapping.cpp \
../app/IOHandler.cpp \
../app/MainApp.cpp \
../app/pins_config.cpp 

OBJS += \
./app/CANopenNode.o \
./app/CiA417_CmdHandler.o \
./app/CiA417_Gateway.o \
./app/FunctionMapping.o \
./app/IOHandler.o \
./app/MainApp.o \
./app/pins_config.o 

CPP_DEPS += \
./app/CANopenNode.d \
./app/CiA417_CmdHandler.d \
./app/CiA417_Gateway.d \
./app/FunctionMapping.d \
./app/IOHandler.d \
./app/MainApp.d \
./app/pins_config.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.cpp app/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -DSTM32F0 -c -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/app" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/basic" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/Hardware_Interface.h" -include"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Tests_tobedeleted/NucleoF072RB_CANSlave/NucleoF072RB_CANSlave/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/STM32F0_Hardware.h" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fexceptions -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/CANopenNode.cyclo ./app/CANopenNode.d ./app/CANopenNode.o ./app/CANopenNode.su ./app/CiA417_CmdHandler.cyclo ./app/CiA417_CmdHandler.d ./app/CiA417_CmdHandler.o ./app/CiA417_CmdHandler.su ./app/CiA417_Gateway.cyclo ./app/CiA417_Gateway.d ./app/CiA417_Gateway.o ./app/CiA417_Gateway.su ./app/FunctionMapping.cyclo ./app/FunctionMapping.d ./app/FunctionMapping.o ./app/FunctionMapping.su ./app/IOHandler.cyclo ./app/IOHandler.d ./app/IOHandler.o ./app/IOHandler.su ./app/MainApp.cyclo ./app/MainApp.d ./app/MainApp.o ./app/MainApp.su ./app/pins_config.cyclo ./app/pins_config.d ./app/pins_config.o ./app/pins_config.su

.PHONY: clean-app

