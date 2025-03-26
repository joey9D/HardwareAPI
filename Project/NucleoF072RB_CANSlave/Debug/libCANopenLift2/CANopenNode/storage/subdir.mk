################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libCANopenLift2/CANopenNode/storage/CO_storage.c \
../libCANopenLift2/CANopenNode/storage/CO_storageEeprom.c 

C_DEPS += \
./libCANopenLift2/CANopenNode/storage/CO_storage.d \
./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.d 

OBJS += \
./libCANopenLift2/CANopenNode/storage/CO_storage.o \
./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.o 


# Each subdirectory must supply rules for building sources it contributes
libCANopenLift2/CANopenNode/storage/%.o libCANopenLift2/CANopenNode/storage/%.su libCANopenLift2/CANopenNode/storage/%.cyclo: ../libCANopenLift2/CANopenNode/storage/%.c libCANopenLift2/CANopenNode/storage/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libCANopenLift2-2f-CANopenNode-2f-storage

clean-libCANopenLift2-2f-CANopenNode-2f-storage:
	-$(RM) ./libCANopenLift2/CANopenNode/storage/CO_storage.cyclo ./libCANopenLift2/CANopenNode/storage/CO_storage.d ./libCANopenLift2/CANopenNode/storage/CO_storage.o ./libCANopenLift2/CANopenNode/storage/CO_storage.su ./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.cyclo ./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.d ./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.o ./libCANopenLift2/CANopenNode/storage/CO_storageEeprom.su

.PHONY: clean-libCANopenLift2-2f-CANopenNode-2f-storage

