################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.c \
../Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.c 

C_DEPS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.d \
./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.d 

OBJS += \
./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.o \
./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.o 


# Each subdirectory must supply rules for building sources it contributes
Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/%.o Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/%.su Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/%.cyclo: ../Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/%.c Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNodeInterface" -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNode" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/Old" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-ESP32

clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-ESP32:
	-$(RM) ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_app_ESP32.su ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.cyclo ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.d ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.o ./Old_and_NewAbstraction/New/Hardware_Abstraction/ESP32/CO_driver_ESP32.su

.PHONY: clean-Old_and_NewAbstraction-2f-New-2f-Hardware_Abstraction-2f-ESP32

