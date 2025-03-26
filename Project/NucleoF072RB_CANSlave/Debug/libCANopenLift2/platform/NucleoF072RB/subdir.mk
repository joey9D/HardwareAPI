################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.c \
../libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.c \
../libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.c 

C_DEPS += \
./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.d \
./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.d \
./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.d 

OBJS += \
./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.o \
./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.o \
./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.o 


# Each subdirectory must supply rules for building sources it contributes
libCANopenLift2/platform/NucleoF072RB/%.o libCANopenLift2/platform/NucleoF072RB/%.su libCANopenLift2/platform/NucleoF072RB/%.cyclo: ../libCANopenLift2/platform/NucleoF072RB/%.c libCANopenLift2/platform/NucleoF072RB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libCANopenLift2-2f-platform-2f-NucleoF072RB

clean-libCANopenLift2-2f-platform-2f-NucleoF072RB:
	-$(RM) ./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.cyclo ./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.d ./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.o ./libCANopenLift2/platform/NucleoF072RB/CO_app_STM32.su ./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.cyclo ./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.d ./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.o ./libCANopenLift2/platform/NucleoF072RB/CO_driver_STM32.su ./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.cyclo ./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.d ./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.o ./libCANopenLift2/platform/NucleoF072RB/CO_storageBlank.su

.PHONY: clean-libCANopenLift2-2f-platform-2f-NucleoF072RB

