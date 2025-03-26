################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libCANopenLift2/dictionaries/LiftTestSlave/OD.c 

C_DEPS += \
./libCANopenLift2/dictionaries/LiftTestSlave/OD.d 

OBJS += \
./libCANopenLift2/dictionaries/LiftTestSlave/OD.o 


# Each subdirectory must supply rules for building sources it contributes
libCANopenLift2/dictionaries/LiftTestSlave/%.o libCANopenLift2/dictionaries/LiftTestSlave/%.su libCANopenLift2/dictionaries/LiftTestSlave/%.cyclo: ../libCANopenLift2/dictionaries/LiftTestSlave/%.c libCANopenLift2/dictionaries/LiftTestSlave/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libCANopenLift2-2f-dictionaries-2f-LiftTestSlave

clean-libCANopenLift2-2f-dictionaries-2f-LiftTestSlave:
	-$(RM) ./libCANopenLift2/dictionaries/LiftTestSlave/OD.cyclo ./libCANopenLift2/dictionaries/LiftTestSlave/OD.d ./libCANopenLift2/dictionaries/LiftTestSlave/OD.o ./libCANopenLift2/dictionaries/LiftTestSlave/OD.su

.PHONY: clean-libCANopenLift2-2f-dictionaries-2f-LiftTestSlave

