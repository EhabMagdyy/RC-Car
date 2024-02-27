################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECU/Buzzer/buzzer.c \
../ECU/Buzzer/buzzer_lcfg.c 

OBJS += \
./ECU/Buzzer/buzzer.o \
./ECU/Buzzer/buzzer_lcfg.o 

C_DEPS += \
./ECU/Buzzer/buzzer.d \
./ECU/Buzzer/buzzer_lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
ECU/Buzzer/%.o ECU/Buzzer/%.su ECU/Buzzer/%.cyclo: ../ECU/Buzzer/%.c ECU/Buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Ehab/Documents/ARM/RC_Car/ECU/Buzzer" -I"C:/Users/Ehab/Documents/ARM/RC_Car/ECU/DCMotor" -I"C:/Users/Ehab/Documents/ARM/RC_Car/ECU/UltrasonicSensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ECU-2f-Buzzer

clean-ECU-2f-Buzzer:
	-$(RM) ./ECU/Buzzer/buzzer.cyclo ./ECU/Buzzer/buzzer.d ./ECU/Buzzer/buzzer.o ./ECU/Buzzer/buzzer.su ./ECU/Buzzer/buzzer_lcfg.cyclo ./ECU/Buzzer/buzzer_lcfg.d ./ECU/Buzzer/buzzer_lcfg.o ./ECU/Buzzer/buzzer_lcfg.su

.PHONY: clean-ECU-2f-Buzzer

