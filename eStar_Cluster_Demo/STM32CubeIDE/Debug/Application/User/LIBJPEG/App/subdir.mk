################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/GitWork_Areas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/LIBJPEG/App/libjpeg.c 

C_DEPS += \
./Application/User/LIBJPEG/App/libjpeg.d 

OBJS += \
./Application/User/LIBJPEG/App/libjpeg.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/LIBJPEG/App/libjpeg.o: D:/GitWork_Areas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/LIBJPEG/App/libjpeg.c Application/User/LIBJPEG/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Application/User/LIBJPEG/App/libjpeg.c_includes.args"

clean: clean-Application-2f-User-2f-LIBJPEG-2f-App

clean-Application-2f-User-2f-LIBJPEG-2f-App:
	-$(RM) ./Application/User/LIBJPEG/App/libjpeg.cyclo ./Application/User/LIBJPEG/App/libjpeg.d ./Application/User/LIBJPEG/App/libjpeg.o ./Application/User/LIBJPEG/App/libjpeg.su

.PHONY: clean-Application-2f-User-2f-LIBJPEG-2f-App

