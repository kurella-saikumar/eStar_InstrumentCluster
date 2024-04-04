################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/list.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

C_DEPS += \
./Middlewares/FreeRTOS/cmsis_os2.d \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/heap_4.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/port.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/stream_buffer.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 

OBJS += \
./Middlewares/FreeRTOS/cmsis_os2.o \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/heap_4.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/port.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/stream_buffer.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/cmsis_os2.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/croutine.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/croutine.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/event_groups.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/heap_4.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/list.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/list.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/port.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/queue.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/queue.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/stream_buffer.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/tasks.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/tasks.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/timers.o: E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Middlewares/Third_Party/FreeRTOS/Source/timers.c Middlewares/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/BatteryVoltage_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/AnalogDebounce" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Indicator_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/FuelGuage" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Damping_Filter" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"E:/GitProjects/eSTAR_InstrumentCluster/eStar_Cluster_Demo/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FreeRTOS

clean-Middlewares-2f-FreeRTOS:
	-$(RM) ./Middlewares/FreeRTOS/cmsis_os2.cyclo ./Middlewares/FreeRTOS/cmsis_os2.d ./Middlewares/FreeRTOS/cmsis_os2.o ./Middlewares/FreeRTOS/cmsis_os2.su ./Middlewares/FreeRTOS/croutine.cyclo ./Middlewares/FreeRTOS/croutine.d ./Middlewares/FreeRTOS/croutine.o ./Middlewares/FreeRTOS/croutine.su ./Middlewares/FreeRTOS/event_groups.cyclo ./Middlewares/FreeRTOS/event_groups.d ./Middlewares/FreeRTOS/event_groups.o ./Middlewares/FreeRTOS/event_groups.su ./Middlewares/FreeRTOS/heap_4.cyclo ./Middlewares/FreeRTOS/heap_4.d ./Middlewares/FreeRTOS/heap_4.o ./Middlewares/FreeRTOS/heap_4.su ./Middlewares/FreeRTOS/list.cyclo ./Middlewares/FreeRTOS/list.d ./Middlewares/FreeRTOS/list.o ./Middlewares/FreeRTOS/list.su ./Middlewares/FreeRTOS/port.cyclo ./Middlewares/FreeRTOS/port.d ./Middlewares/FreeRTOS/port.o ./Middlewares/FreeRTOS/port.su ./Middlewares/FreeRTOS/queue.cyclo ./Middlewares/FreeRTOS/queue.d ./Middlewares/FreeRTOS/queue.o ./Middlewares/FreeRTOS/queue.su ./Middlewares/FreeRTOS/stream_buffer.cyclo ./Middlewares/FreeRTOS/stream_buffer.d ./Middlewares/FreeRTOS/stream_buffer.o ./Middlewares/FreeRTOS/stream_buffer.su ./Middlewares/FreeRTOS/tasks.cyclo ./Middlewares/FreeRTOS/tasks.d ./Middlewares/FreeRTOS/tasks.o ./Middlewares/FreeRTOS/tasks.su ./Middlewares/FreeRTOS/timers.cyclo ./Middlewares/FreeRTOS/timers.d ./Middlewares/FreeRTOS/timers.o ./Middlewares/FreeRTOS/timers.su

.PHONY: clean-Middlewares-2f-FreeRTOS

