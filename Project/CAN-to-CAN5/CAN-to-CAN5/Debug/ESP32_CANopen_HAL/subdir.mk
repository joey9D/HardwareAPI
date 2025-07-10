################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ESP32_CANopen_HAL/CO_app_ESP32.c \
../ESP32_CANopen_HAL/CO_driver_ESP32.c \
../ESP32_CANopen_HAL/CO_storageBlank.c \
../ESP32_CANopen_HAL/OD.c 

C_DEPS += \
./ESP32_CANopen_HAL/CO_app_ESP32.d \
./ESP32_CANopen_HAL/CO_driver_ESP32.d \
./ESP32_CANopen_HAL/CO_storageBlank.d \
./ESP32_CANopen_HAL/OD.d 

OBJS += \
./ESP32_CANopen_HAL/CO_app_ESP32.o \
./ESP32_CANopen_HAL/CO_driver_ESP32.o \
./ESP32_CANopen_HAL/CO_storageBlank.o \
./ESP32_CANopen_HAL/OD.o 


# Each subdirectory must supply rules for building sources it contributes
ESP32_CANopen_HAL/%.o ESP32_CANopen_HAL/%.su ESP32_CANopen_HAL/%.cyclo: ../ESP32_CANopen_HAL/%.c ESP32_CANopen_HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/Updated_IO/HeaderFiles" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNodeInterface" -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/CANopenNode" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN/Old_and_NewAbstraction/Old" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ESP32_CANopen_HAL

clean-ESP32_CANopen_HAL:
	-$(RM) ./ESP32_CANopen_HAL/CO_app_ESP32.cyclo ./ESP32_CANopen_HAL/CO_app_ESP32.d ./ESP32_CANopen_HAL/CO_app_ESP32.o ./ESP32_CANopen_HAL/CO_app_ESP32.su ./ESP32_CANopen_HAL/CO_driver_ESP32.cyclo ./ESP32_CANopen_HAL/CO_driver_ESP32.d ./ESP32_CANopen_HAL/CO_driver_ESP32.o ./ESP32_CANopen_HAL/CO_driver_ESP32.su ./ESP32_CANopen_HAL/CO_storageBlank.cyclo ./ESP32_CANopen_HAL/CO_storageBlank.d ./ESP32_CANopen_HAL/CO_storageBlank.o ./ESP32_CANopen_HAL/CO_storageBlank.su ./ESP32_CANopen_HAL/OD.cyclo ./ESP32_CANopen_HAL/OD.d ./ESP32_CANopen_HAL/OD.o ./ESP32_CANopen_HAL/OD.su

.PHONY: clean-ESP32_CANopen_HAL

