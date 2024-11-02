################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.c 

C_DEPS += \
./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.d 

OBJS += \
./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/InstrumentClusterInit/%.o Application/User/Core/InstrumentClusterInit/%.su Application/User/Core/InstrumentClusterInit/%.cyclo: ../Application/User/Core/InstrumentClusterInit/%.c Application/User/Core/InstrumentClusterInit/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-InstrumentClusterInit

clean-Application-2f-User-2f-Core-2f-InstrumentClusterInit:
	-$(RM) ./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.cyclo ./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.d ./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.o ./Application/User/Core/InstrumentClusterInit/InstrumentClusterInit.su

.PHONY: clean-Application-2f-User-2f-Core-2f-InstrumentClusterInit

