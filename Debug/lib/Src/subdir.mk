################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/Src/my_nmea.c 

OBJS += \
./lib/Src/my_nmea.o 

C_DEPS += \
./lib/Src/my_nmea.d 


# Each subdirectory must supply rules for building sources it contributes
lib/Src/%.o lib/Src/%.su lib/Src/%.cyclo: ../lib/Src/%.c lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G031K8Tx -c -I../Inc -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Include" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Device/ST/STM32G0xx/Include" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/CMSIS/Device/ST/STM32G0xx/Source" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/my_drivers/Inc" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/my_drivers/Src" -I"C:/Users/mzeml/embedded/Tuto_UART_REG_G031_002/lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib-2f-Src

clean-lib-2f-Src:
	-$(RM) ./lib/Src/my_nmea.cyclo ./lib/Src/my_nmea.d ./lib/Src/my_nmea.o ./lib/Src/my_nmea.su

.PHONY: clean-lib-2f-Src

