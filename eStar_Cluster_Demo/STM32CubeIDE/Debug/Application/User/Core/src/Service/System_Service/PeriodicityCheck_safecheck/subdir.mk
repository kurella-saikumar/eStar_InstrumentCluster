################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.c 

C_DEPS += \
./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.d 

OBJS += \
./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/%.o Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/%.su Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/%.cyclo: ../Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/%.c Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-PeriodicityCheck_safecheck

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-PeriodicityCheck_safecheck:
	-$(RM) ./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.cyclo ./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.d ./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.o ./Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck/PeriodicityCheck.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-PeriodicityCheck_safecheck

