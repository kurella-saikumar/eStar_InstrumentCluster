################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.c 

C_DEPS += \
./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.d 

OBJS += \
./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/%.o Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/%.su Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/%.cyclo: ../Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/%.c Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/ServiceRequest_App" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Task_ExeTime" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/PeriodicityCheck" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Stack_Usage" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Task_Overload_Deadlock" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Clock_App" -I../../Core/Inc -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/DriverInfo_App/DriverInfoApp.h" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/checksum" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/CAN/CAN_IF" -I"D:/estar_GIT/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/CAN/CAN_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-flash_interface

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-flash_interface:
	-$(RM) ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.cyclo ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.d ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.o ./Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface/flash_interface.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-Memory_Service-2f-eeprom_emul-2f-flash_interface

