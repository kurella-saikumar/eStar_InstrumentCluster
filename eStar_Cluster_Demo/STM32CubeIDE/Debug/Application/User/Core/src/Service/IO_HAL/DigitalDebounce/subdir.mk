################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.c 

C_DEPS += \
./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.d 

OBJS += \
./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/IO_HAL/DigitalDebounce/%.o Application/User/Core/src/Service/IO_HAL/DigitalDebounce/%.su Application/User/Core/src/Service/IO_HAL/DigitalDebounce/%.cyclo: ../Application/User/Core/src/Service/IO_HAL/DigitalDebounce/%.c Application/User/Core/src/Service/IO_HAL/DigitalDebounce/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-DigitalDebounce

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-DigitalDebounce:
	-$(RM) ./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.cyclo ./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.d ./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.o ./Application/User/Core/src/Service/IO_HAL/DigitalDebounce/digital_debounce.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-DigitalDebounce

