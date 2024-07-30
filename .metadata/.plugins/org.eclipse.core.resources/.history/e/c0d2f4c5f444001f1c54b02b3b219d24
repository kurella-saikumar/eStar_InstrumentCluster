################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.c 

C_DEPS += \
./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.d 

OBJS += \
./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/App/ServiceRequest_App/%.o Application/User/Core/src/App/ServiceRequest_App/%.su Application/User/Core/src/App/ServiceRequest_App/%.cyclo: ../Application/User/Core/src/App/ServiceRequest_App/%.c Application/User/Core/src/App/ServiceRequest_App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-ServiceRequest_App

clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-ServiceRequest_App:
	-$(RM) ./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.cyclo ./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.d ./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.o ./Application/User/Core/src/App/ServiceRequest_App/ServiceRequest_App.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-ServiceRequest_App

