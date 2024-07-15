################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.c 

C_DEPS += \
./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.d 

OBJS += \
./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/%.o Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/%.su Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/%.cyclo: ../Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/%.c Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-eeprom_emulation

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-eeprom_emulation:
	-$(RM) ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.cyclo ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.d ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.o ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation/eeprom_emul.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-eeprom_emulation

