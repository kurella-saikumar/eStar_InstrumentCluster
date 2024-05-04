################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/App/FuelGuage/FuelGuage_App.c 

C_DEPS += \
./Application/User/Core/src/App/FuelGuage/FuelGuage_App.d 

OBJS += \
./Application/User/Core/src/App/FuelGuage/FuelGuage_App.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/App/FuelGuage/%.o Application/User/Core/src/App/FuelGuage/%.su Application/User/Core/src/App/FuelGuage/%.cyclo: ../Application/User/Core/src/App/FuelGuage/%.c Application/User/Core/src/App/FuelGuage/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Clock_App" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/DriverInfoApplication" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/CAN_App" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-FuelGuage

clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-FuelGuage:
	-$(RM) ./Application/User/Core/src/App/FuelGuage/FuelGuage_App.cyclo ./Application/User/Core/src/App/FuelGuage/FuelGuage_App.d ./Application/User/Core/src/App/FuelGuage/FuelGuage_App.o ./Application/User/Core/src/App/FuelGuage/FuelGuage_App.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-App-2f-FuelGuage

