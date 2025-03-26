################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libCANopenLift2/CANopenNode/301/CO_Emergency.c \
../libCANopenLift2/CANopenNode/301/CO_HBconsumer.c \
../libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.c \
../libCANopenLift2/CANopenNode/301/CO_ODinterface.c \
../libCANopenLift2/CANopenNode/301/CO_PDO.c \
../libCANopenLift2/CANopenNode/301/CO_SDOclient.c \
../libCANopenLift2/CANopenNode/301/CO_SDOserver.c \
../libCANopenLift2/CANopenNode/301/CO_SYNC.c \
../libCANopenLift2/CANopenNode/301/CO_TIME.c \
../libCANopenLift2/CANopenNode/301/CO_fifo.c \
../libCANopenLift2/CANopenNode/301/crc16-ccitt.c 

C_DEPS += \
./libCANopenLift2/CANopenNode/301/CO_Emergency.d \
./libCANopenLift2/CANopenNode/301/CO_HBconsumer.d \
./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.d \
./libCANopenLift2/CANopenNode/301/CO_ODinterface.d \
./libCANopenLift2/CANopenNode/301/CO_PDO.d \
./libCANopenLift2/CANopenNode/301/CO_SDOclient.d \
./libCANopenLift2/CANopenNode/301/CO_SDOserver.d \
./libCANopenLift2/CANopenNode/301/CO_SYNC.d \
./libCANopenLift2/CANopenNode/301/CO_TIME.d \
./libCANopenLift2/CANopenNode/301/CO_fifo.d \
./libCANopenLift2/CANopenNode/301/crc16-ccitt.d 

OBJS += \
./libCANopenLift2/CANopenNode/301/CO_Emergency.o \
./libCANopenLift2/CANopenNode/301/CO_HBconsumer.o \
./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.o \
./libCANopenLift2/CANopenNode/301/CO_ODinterface.o \
./libCANopenLift2/CANopenNode/301/CO_PDO.o \
./libCANopenLift2/CANopenNode/301/CO_SDOclient.o \
./libCANopenLift2/CANopenNode/301/CO_SDOserver.o \
./libCANopenLift2/CANopenNode/301/CO_SYNC.o \
./libCANopenLift2/CANopenNode/301/CO_TIME.o \
./libCANopenLift2/CANopenNode/301/CO_fifo.o \
./libCANopenLift2/CANopenNode/301/crc16-ccitt.o 


# Each subdirectory must supply rules for building sources it contributes
libCANopenLift2/CANopenNode/301/%.o libCANopenLift2/CANopenNode/301/%.su libCANopenLift2/CANopenNode/301/%.cyclo: ../libCANopenLift2/CANopenNode/301/%.c libCANopenLift2/CANopenNode/301/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode -I../CANopenNodeInterface -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libCANopenLift2-2f-CANopenNode-2f-301

clean-libCANopenLift2-2f-CANopenNode-2f-301:
	-$(RM) ./libCANopenLift2/CANopenNode/301/CO_Emergency.cyclo ./libCANopenLift2/CANopenNode/301/CO_Emergency.d ./libCANopenLift2/CANopenNode/301/CO_Emergency.o ./libCANopenLift2/CANopenNode/301/CO_Emergency.su ./libCANopenLift2/CANopenNode/301/CO_HBconsumer.cyclo ./libCANopenLift2/CANopenNode/301/CO_HBconsumer.d ./libCANopenLift2/CANopenNode/301/CO_HBconsumer.o ./libCANopenLift2/CANopenNode/301/CO_HBconsumer.su ./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.cyclo ./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.d ./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.o ./libCANopenLift2/CANopenNode/301/CO_NMT_Heartbeat.su ./libCANopenLift2/CANopenNode/301/CO_ODinterface.cyclo ./libCANopenLift2/CANopenNode/301/CO_ODinterface.d ./libCANopenLift2/CANopenNode/301/CO_ODinterface.o ./libCANopenLift2/CANopenNode/301/CO_ODinterface.su ./libCANopenLift2/CANopenNode/301/CO_PDO.cyclo ./libCANopenLift2/CANopenNode/301/CO_PDO.d ./libCANopenLift2/CANopenNode/301/CO_PDO.o ./libCANopenLift2/CANopenNode/301/CO_PDO.su ./libCANopenLift2/CANopenNode/301/CO_SDOclient.cyclo ./libCANopenLift2/CANopenNode/301/CO_SDOclient.d ./libCANopenLift2/CANopenNode/301/CO_SDOclient.o ./libCANopenLift2/CANopenNode/301/CO_SDOclient.su ./libCANopenLift2/CANopenNode/301/CO_SDOserver.cyclo ./libCANopenLift2/CANopenNode/301/CO_SDOserver.d ./libCANopenLift2/CANopenNode/301/CO_SDOserver.o ./libCANopenLift2/CANopenNode/301/CO_SDOserver.su ./libCANopenLift2/CANopenNode/301/CO_SYNC.cyclo ./libCANopenLift2/CANopenNode/301/CO_SYNC.d ./libCANopenLift2/CANopenNode/301/CO_SYNC.o ./libCANopenLift2/CANopenNode/301/CO_SYNC.su ./libCANopenLift2/CANopenNode/301/CO_TIME.cyclo ./libCANopenLift2/CANopenNode/301/CO_TIME.d ./libCANopenLift2/CANopenNode/301/CO_TIME.o ./libCANopenLift2/CANopenNode/301/CO_TIME.su ./libCANopenLift2/CANopenNode/301/CO_fifo.cyclo ./libCANopenLift2/CANopenNode/301/CO_fifo.d ./libCANopenLift2/CANopenNode/301/CO_fifo.o ./libCANopenLift2/CANopenNode/301/CO_fifo.su ./libCANopenLift2/CANopenNode/301/crc16-ccitt.cyclo ./libCANopenLift2/CANopenNode/301/crc16-ccitt.d ./libCANopenLift2/CANopenNode/301/crc16-ccitt.o ./libCANopenLift2/CANopenNode/301/crc16-ccitt.su

.PHONY: clean-libCANopenLift2-2f-CANopenNode-2f-301

