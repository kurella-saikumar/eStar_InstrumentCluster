################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/IO_HAL/Switch/switch.c 

C_DEPS += \
./Application/User/Core/src/Service/IO_HAL/Switch/switch.d 

OBJS += \
./Application/User/Core/src/Service/IO_HAL/Switch/switch.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/IO_HAL/Switch/%.o Application/User/Core/src/Service/IO_HAL/Switch/%.su Application/User/Core/src/Service/IO_HAL/Switch/%.cyclo: ../Application/User/Core/src/Service/IO_HAL/Switch/%.c Application/User/Core/src/Service/IO_HAL/Switch/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/IO_HAL/Switch/switch.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-Switch

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-Switch:
	-$(RM) ./Application/User/Core/src/Service/IO_HAL/Switch/switch.cyclo ./Application/User/Core/src/Service/IO_HAL/Switch/switch.d ./Application/User/Core/src/Service/IO_HAL/Switch/switch.o ./Application/User/Core/src/Service/IO_HAL/Switch/switch.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-Switch

