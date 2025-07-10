################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CANopenNode/example/CO_driver_blank.c \
../CANopenNode/example/CO_storageBlank.c \
../CANopenNode/example/OD.c \
../CANopenNode/example/main_blank.c 

C_DEPS += \
./CANopenNode/example/CO_driver_blank.d \
./CANopenNode/example/CO_storageBlank.d \
./CANopenNode/example/OD.d \
./CANopenNode/example/main_blank.d 

OBJS += \
./CANopenNode/example/CO_driver_blank.o \
./CANopenNode/example/CO_storageBlank.o \
./CANopenNode/example/OD.o \
./CANopenNode/example/main_blank.o 


# Each subdirectory must supply rules for building sources it contributes
CANopenNode/example/%.o CANopenNode/example/%.su CANopenNode/example/%.cyclo: ../CANopenNode/example/%.c CANopenNode/example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DBOARD_STM32G0_DEV -DBOARD_STM32G0_CAN_CAN -DSTM32G0 -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Drivers/STM32G0xx_HAL_Driver/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/Common" -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/CANopenNode" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/CANopenNodeInterface" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/Old_and_NewAbstraction/New/Hardware_Abstraction/Includes" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/basic" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/app/Updated_IO/HeaderFiles" -I../Core/Inc -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/app" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/app/RS485" -I"C:/Users/ketan.singh/Desktop/Microcontroller-Nucleo-G071RB/Mustercopy/CAN-to-CAN4/Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32G0/Boards" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CANopenNode-2f-example

clean-CANopenNode-2f-example:
	-$(RM) ./CANopenNode/example/CO_driver_blank.cyclo ./CANopenNode/example/CO_driver_blank.d ./CANopenNode/example/CO_driver_blank.o ./CANopenNode/example/CO_driver_blank.su ./CANopenNode/example/CO_storageBlank.cyclo ./CANopenNode/example/CO_storageBlank.d ./CANopenNode/example/CO_storageBlank.o ./CANopenNode/example/CO_storageBlank.su ./CANopenNode/example/OD.cyclo ./CANopenNode/example/OD.d ./CANopenNode/example/OD.o ./CANopenNode/example/OD.su ./CANopenNode/example/main_blank.cyclo ./CANopenNode/example/main_blank.d ./CANopenNode/example/main_blank.o ./CANopenNode/example/main_blank.su

.PHONY: clean-CANopenNode-2f-example

