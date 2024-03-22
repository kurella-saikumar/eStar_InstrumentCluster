################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c \
D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c \
D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.d \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.d \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o: D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/APP/DriverInfoApplication" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o: D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/APP/DriverInfoApplication" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o: D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/APP/DriverInfoApplication" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/Govind_WorkSpace/Github_Workspace/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK

clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK:
	-$(RM) ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.su ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.su ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK

