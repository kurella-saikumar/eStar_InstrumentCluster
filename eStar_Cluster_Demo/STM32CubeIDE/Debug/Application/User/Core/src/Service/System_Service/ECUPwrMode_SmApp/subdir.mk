################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.c \
../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.c 

C_DEPS += \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.d \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.d 

OBJS += \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.o \
./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.o Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.su Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.cyclo: ../Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/%.c Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/Watchdog_service" -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/Projects/Git_WorkSpace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp:
	-$(RM) ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.cyclo ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.d ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.o ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler.su ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.cyclo ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.d ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.o ./Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp/ECUPwrMode_SmHandler_Demo.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-ECUPwrMode_SmApp

