################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.c 

C_DEPS += \
./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.d 

OBJS += \
./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/IO_HAL/ICU_middleware/%.o Application/User/Core/src/Service/IO_HAL/ICU_middleware/%.su Application/User/Core/src/Service/IO_HAL/ICU_middleware/%.cyclo: ../Application/User/Core/src/Service/IO_HAL/ICU_middleware/%.c Application/User/Core/src/Service/IO_HAL/ICU_middleware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-ICU_middleware

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-ICU_middleware:
	-$(RM) ./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.cyclo ./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.d ./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.o ./Application/User/Core/src/Service/IO_HAL/ICU_middleware/ICU_driver.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-IO_HAL-2f-ICU_middleware

