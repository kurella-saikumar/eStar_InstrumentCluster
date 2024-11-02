################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/DisplayInit/DisplayInit.c 

C_DEPS += \
./Application/User/Core/DisplayInit/DisplayInit.d 

OBJS += \
./Application/User/Core/DisplayInit/DisplayInit.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/DisplayInit/%.o Application/User/Core/DisplayInit/%.su Application/User/Core/DisplayInit/%.cyclo: ../Application/User/Core/DisplayInit/%.c Application/User/Core/DisplayInit/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/DisplayInit/DisplayInit.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-DisplayInit

clean-Application-2f-User-2f-Core-2f-DisplayInit:
	-$(RM) ./Application/User/Core/DisplayInit/DisplayInit.cyclo ./Application/User/Core/DisplayInit/DisplayInit.d ./Application/User/Core/DisplayInit/DisplayInit.o ./Application/User/Core/DisplayInit/DisplayInit.su

.PHONY: clean-Application-2f-User-2f-Core-2f-DisplayInit

