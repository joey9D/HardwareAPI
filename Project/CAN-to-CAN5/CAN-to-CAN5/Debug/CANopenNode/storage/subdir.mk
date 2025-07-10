################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/storage/CO_storage.c \
../CANopenNode/storage/CO_storageEeprom.c 

C_DEPS += \
./CANopenNode/storage/CO_storage.d \
./CANopenNode/storage/CO_storageEeprom.d 

OBJS += \
./CANopenNode/storage/CO_storage.o \
./CANopenNode/storage/CO_storageEeprom.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/storage/%.o CANopenNode/storage/%.su CANopenNode/storage/%.cyclo: ../CANopenNode/storage/%.c CANopenNode/storage/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Drivers/STM32G0xx_HAL_Driver/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/Updated_IO/HeaderFiles" -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN5/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/Boards" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-storage

clean-CANopenNode-2f-storage:
	-$(RM) ./CANopenNode/storage/CO_storage.cyclo ./CANopenNode/storage/CO_storage.d ./CANopenNode/storage/CO_storage.o ./CANopenNode/storage/CO_storage.su ./CANopenNode/storage/CO_storageEeprom.cyclo ./CANopenNode/storage/CO_storageEeprom.d ./CANopenNode/storage/CO_storageEeprom.o ./CANopenNode/storage/CO_storageEeprom.su

.PHONY: clean-CANopenNode-2f-storage

