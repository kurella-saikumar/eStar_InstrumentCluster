################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/AppTask/AppTask.c 

C_DEPS += \
./Application/User/Core/AppTask/AppTask.d 

OBJS += \
./Application/User/Core/AppTask/AppTask.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/AppTask/%.o Application/User/Core/AppTask/%.su Application/User/Core/AppTask/%.cyclo: ../Application/User/Core/AppTask/%.c Application/User/Core/AppTask/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/AppTask/AppTask.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-AppTask

clean-Application-2f-User-2f-Core-2f-AppTask:
	-$(RM) ./Application/User/Core/AppTask/AppTask.cyclo ./Application/User/Core/AppTask/AppTask.d ./Application/User/Core/AppTask/AppTask.o ./Application/User/Core/AppTask/AppTask.su

.PHONY: clean-Application-2f-User-2f-Core-2f-AppTask

