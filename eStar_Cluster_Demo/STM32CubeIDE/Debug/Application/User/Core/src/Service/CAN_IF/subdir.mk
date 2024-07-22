################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.c \
../Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.c \
../Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.c 

C_DEPS += \
./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.d \
./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.d \
./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.d 

OBJS += \
./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.o \
./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.o \
./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/CAN_IF/%.o Application/User/Core/src/Service/CAN_IF/%.su Application/User/Core/src/Service/CAN_IF/%.cyclo: ../Application/User/Core/src/Service/CAN_IF/%.c Application/User/Core/src/Service/CAN_IF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-CAN_IF

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-CAN_IF:
	-$(RM) ./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.cyclo ./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.d ./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.o ./Application/User/Core/src/Service/CAN_IF/CAN_NIM_Signal_IF.su ./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.cyclo ./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.d ./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.o ./Application/User/Core/src/Service/CAN_IF/Can_NIM_MsgHandler.su ./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.cyclo ./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.d ./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.o ./Application/User/Core/src/Service/CAN_IF/Indicators_CANSignal.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-CAN_IF

