################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CANopenNodeInterface/CanNode.cpp \
../CANopenNodeInterface/CanStackInterface.cpp \
../CANopenNodeInterface/iCanOpenNode.cpp 

C_SRCS += \
../CANopenNodeInterface/CO_app_STM32.c \
../CANopenNodeInterface/CO_driver_STM32.c \
../CANopenNodeInterface/CO_storageBlank.c \
../CANopenNodeInterface/OD.c 

C_DEPS += \
./CANopenNodeInterface/CO_app_STM32.d \
./CANopenNodeInterface/CO_driver_STM32.d \
./CANopenNodeInterface/CO_storageBlank.d \
./CANopenNodeInterface/OD.d 

OBJS += \
./CANopenNodeInterface/CO_app_STM32.o \
./CANopenNodeInterface/CO_driver_STM32.o \
./CANopenNodeInterface/CO_storageBlank.o \
./CANopenNodeInterface/CanNode.o \
./CANopenNodeInterface/CanStackInterface.o \
./CANopenNodeInterface/OD.o \
./CANopenNodeInterface/iCanOpenNode.o 

CPP_DEPS += \
./CANopenNodeInterface/CanNode.d \
./CANopenNodeInterface/CanStackInterface.d \
./CANopenNodeInterface/iCanOpenNode.d 


# Each subdirectory must supply rules for building sources it contributes
CANopenNodeInterface/%.o CANopenNodeInterface/%.su CANopenNodeInterface/%.cyclo: ../CANopenNodeInterface/%.c CANopenNodeInterface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
CANopenNodeInterface/%.o CANopenNodeInterface/%.su CANopenNodeInterface/%.cyclo: ../CANopenNodeInterface/%.cpp CANopenNodeInterface/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++17 -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNodeInterface

clean-CANopenNodeInterface:
	-$(RM) ./CANopenNodeInterface/CO_app_STM32.cyclo ./CANopenNodeInterface/CO_app_STM32.d ./CANopenNodeInterface/CO_app_STM32.o ./CANopenNodeInterface/CO_app_STM32.su ./CANopenNodeInterface/CO_driver_STM32.cyclo ./CANopenNodeInterface/CO_driver_STM32.d ./CANopenNodeInterface/CO_driver_STM32.o ./CANopenNodeInterface/CO_driver_STM32.su ./CANopenNodeInterface/CO_storageBlank.cyclo ./CANopenNodeInterface/CO_storageBlank.d ./CANopenNodeInterface/CO_storageBlank.o ./CANopenNodeInterface/CO_storageBlank.su ./CANopenNodeInterface/CanNode.cyclo ./CANopenNodeInterface/CanNode.d ./CANopenNodeInterface/CanNode.o ./CANopenNodeInterface/CanNode.su ./CANopenNodeInterface/CanStackInterface.cyclo ./CANopenNodeInterface/CanStackInterface.d ./CANopenNodeInterface/CanStackInterface.o ./CANopenNodeInterface/CanStackInterface.su ./CANopenNodeInterface/OD.cyclo ./CANopenNodeInterface/OD.d ./CANopenNodeInterface/OD.o ./CANopenNodeInterface/OD.su ./CANopenNodeInterface/iCanOpenNode.cyclo ./CANopenNodeInterface/iCanOpenNode.d ./CANopenNodeInterface/iCanOpenNode.o ./CANopenNodeInterface/iCanOpenNode.su

.PHONY: clean-CANopenNodeInterface

