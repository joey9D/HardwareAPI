################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libCANopenLift2/CANopenNode/305/CO_LSSmaster.c \
../libCANopenLift2/CANopenNode/305/CO_LSSslave.c 

C_DEPS += \
./libCANopenLift2/CANopenNode/305/CO_LSSmaster.d \
./libCANopenLift2/CANopenNode/305/CO_LSSslave.d 

OBJS += \
./libCANopenLift2/CANopenNode/305/CO_LSSmaster.o \
./libCANopenLift2/CANopenNode/305/CO_LSSslave.o 


# Each subdirectory must supply rules for building sources it contributes
libCANopenLift2/CANopenNode/305/%.o libCANopenLift2/CANopenNode/305/%.su libCANopenLift2/CANopenNode/305/%.cyclo: ../libCANopenLift2/CANopenNode/305/%.c libCANopenLift2/CANopenNode/305/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libCANopenLift2-2f-CANopenNode-2f-305

clean-libCANopenLift2-2f-CANopenNode-2f-305:
	-$(RM) ./libCANopenLift2/CANopenNode/305/CO_LSSmaster.cyclo ./libCANopenLift2/CANopenNode/305/CO_LSSmaster.d ./libCANopenLift2/CANopenNode/305/CO_LSSmaster.o ./libCANopenLift2/CANopenNode/305/CO_LSSmaster.su ./libCANopenLift2/CANopenNode/305/CO_LSSslave.cyclo ./libCANopenLift2/CANopenNode/305/CO_LSSslave.d ./libCANopenLift2/CANopenNode/305/CO_LSSslave.o ./libCANopenLift2/CANopenNode/305/CO_LSSslave.su

.PHONY: clean-libCANopenLift2-2f-CANopenNode-2f-305

