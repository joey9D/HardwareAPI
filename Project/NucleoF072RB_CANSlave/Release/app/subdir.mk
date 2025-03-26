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
../app/MainApp.cpp 

OBJS += \
./app/CANopenNode.o \
./app/CiA417_CmdHandler.o \
./app/CiA417_Gateway.o \
./app/FunctionMapping.o \
./app/MainApp.o 

CPP_DEPS += \
./app/CANopenNode.d \
./app/CiA417_CmdHandler.d \
./app/CiA417_Gateway.d \
./app/FunctionMapping.d \
./app/MainApp.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.cpp app/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/CANopenNode.cyclo ./app/CANopenNode.d ./app/CANopenNode.o ./app/CANopenNode.su ./app/CiA417_CmdHandler.cyclo ./app/CiA417_CmdHandler.d ./app/CiA417_CmdHandler.o ./app/CiA417_CmdHandler.su ./app/CiA417_Gateway.cyclo ./app/CiA417_Gateway.d ./app/CiA417_Gateway.o ./app/CiA417_Gateway.su ./app/FunctionMapping.cyclo ./app/FunctionMapping.d ./app/FunctionMapping.o ./app/FunctionMapping.su ./app/MainApp.cyclo ./app/MainApp.d ./app/MainApp.o ./app/MainApp.su

.PHONY: clean-app

