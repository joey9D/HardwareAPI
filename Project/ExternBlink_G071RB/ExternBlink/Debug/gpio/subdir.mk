################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gpio/gpio_base.cpp \
../gpio/gpio_stm32.cpp \
../gpio/output_base.cpp \
../gpio/output_stm32.cpp 

OBJS += \
./gpio/gpio_base.o \
./gpio/gpio_stm32.o \
./gpio/output_base.o \
./gpio/output_stm32.o 

CPP_DEPS += \
./gpio/gpio_base.d \
./gpio/gpio_stm32.d \
./gpio/output_base.d \
./gpio/output_stm32.d 


# Each subdirectory must supply rules for building sources it contributes
gpio/%.o gpio/%.su gpio/%.cyclo: ../gpio/%.cpp gpio/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jan.kristel/STM32CubeIDE/Thesis/ExternBlink/gpio" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

clean: clean-gpio

clean-gpio:
	-$(RM) ./gpio/gpio_base.cyclo ./gpio/gpio_base.d ./gpio/gpio_base.o ./gpio/gpio_base.su ./gpio/gpio_stm32.cyclo ./gpio/gpio_stm32.d ./gpio/gpio_stm32.o ./gpio/gpio_stm32.su ./gpio/output_base.cyclo ./gpio/output_base.d ./gpio/output_base.o ./gpio/output_base.su ./gpio/output_stm32.cyclo ./gpio/output_stm32.d ./gpio/output_stm32.o ./gpio/output_stm32.su

.PHONY: clean-gpio

