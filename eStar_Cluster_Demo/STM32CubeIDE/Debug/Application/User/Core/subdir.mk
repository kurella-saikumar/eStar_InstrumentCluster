################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/AppTask.c \
../Application/User/Core/DisplayInit.c \
../Application/User/Core/InstrumentClusterInit.c \
../Application/User/Core/SafetyCheckPluginDemo.c \
../Application/User/Core/freertos.c \
../Application/User/Core/main.c \
../Application/User/Core/stm32h7xx_hal_msp.c \
../Application/User/Core/stm32h7xx_hal_timebase_tim.c \
../Application/User/Core/stm32h7xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c 

C_DEPS += \
./Application/User/Core/AppTask.d \
./Application/User/Core/DisplayInit.d \
./Application/User/Core/InstrumentClusterInit.d \
./Application/User/Core/SafetyCheckPluginDemo.d \
./Application/User/Core/freertos.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32h7xx_hal_msp.d \
./Application/User/Core/stm32h7xx_hal_timebase_tim.d \
./Application/User/Core/stm32h7xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d 

OBJS += \
./Application/User/Core/AppTask.o \
./Application/User/Core/DisplayInit.o \
./Application/User/Core/InstrumentClusterInit.o \
./Application/User/Core/SafetyCheckPluginDemo.o \
./Application/User/Core/freertos.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32h7xx_hal_msp.o \
./Application/User/Core/stm32h7xx_hal_timebase_tim.o \
./Application/User/Core/stm32h7xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/Core/AppTask.c_includes.args"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/AppTask.cyclo ./Application/User/Core/AppTask.d ./Application/User/Core/AppTask.o ./Application/User/Core/AppTask.su ./Application/User/Core/DisplayInit.cyclo ./Application/User/Core/DisplayInit.d ./Application/User/Core/DisplayInit.o ./Application/User/Core/DisplayInit.su ./Application/User/Core/InstrumentClusterInit.cyclo ./Application/User/Core/InstrumentClusterInit.d ./Application/User/Core/InstrumentClusterInit.o ./Application/User/Core/InstrumentClusterInit.su ./Application/User/Core/SafetyCheckPluginDemo.cyclo ./Application/User/Core/SafetyCheckPluginDemo.d ./Application/User/Core/SafetyCheckPluginDemo.o ./Application/User/Core/SafetyCheckPluginDemo.su ./Application/User/Core/freertos.cyclo ./Application/User/Core/freertos.d ./Application/User/Core/freertos.o ./Application/User/Core/freertos.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32h7xx_hal_msp.cyclo ./Application/User/Core/stm32h7xx_hal_msp.d ./Application/User/Core/stm32h7xx_hal_msp.o ./Application/User/Core/stm32h7xx_hal_msp.su ./Application/User/Core/stm32h7xx_hal_timebase_tim.cyclo ./Application/User/Core/stm32h7xx_hal_timebase_tim.d ./Application/User/Core/stm32h7xx_hal_timebase_tim.o ./Application/User/Core/stm32h7xx_hal_timebase_tim.su ./Application/User/Core/stm32h7xx_it.cyclo ./Application/User/Core/stm32h7xx_it.d ./Application/User/Core/stm32h7xx_it.o ./Application/User/Core/stm32h7xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su

.PHONY: clean-Application-2f-User-2f-Core

