################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.c \
../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.c \
../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.c 

C_DEPS += \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.d \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.d \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.d 

OBJS += \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.o \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.o \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.o Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.su Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.cyclo: ../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.c Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.c_includes.args"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp:
	-$(RM) ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.cyclo ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.d ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.o ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.su ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.cyclo ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.d ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.o ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.su ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.cyclo ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.d ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.o ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/Sys_WakeUp_Reason.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp

