################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/parse_nmea.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/parse_nmea.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/parse_nmea.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G031K8Tx -c -I../Inc -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Include" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Device/ST/STM32G0xx/Include" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Device/ST/STM32G0xx/Source" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/my_drivers/Inc" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/my_drivers/Src" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/parse_nmea.cyclo ./Src/parse_nmea.d ./Src/parse_nmea.o ./Src/parse_nmea.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

