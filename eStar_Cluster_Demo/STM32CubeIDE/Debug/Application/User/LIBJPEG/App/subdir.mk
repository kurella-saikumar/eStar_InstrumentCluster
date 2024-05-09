################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/LIBJPEG/App/libjpeg.c 

C_DEPS += \
./Application/User/LIBJPEG/App/libjpeg.d 

OBJS += \
./Application/User/LIBJPEG/App/libjpeg.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/LIBJPEG/App/libjpeg.o: D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/LIBJPEG/App/libjpeg.c Application/User/LIBJPEG/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/ServiceRequest_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Clock_App" -I../../Core/Inc -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/DriverInfoApplication" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/CAN_App" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/TimeExe_SafeChecks" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/PeriodicityCheck_safecheck" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/StackUsage_SafeChecks" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-LIBJPEG-2f-App

clean-Application-2f-User-2f-LIBJPEG-2f-App:
	-$(RM) ./Application/User/LIBJPEG/App/libjpeg.cyclo ./Application/User/LIBJPEG/App/libjpeg.d ./Application/User/LIBJPEG/App/libjpeg.o ./Application/User/LIBJPEG/App/libjpeg.su

.PHONY: clean-Application-2f-User-2f-LIBJPEG-2f-App

