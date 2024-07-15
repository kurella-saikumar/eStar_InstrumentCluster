################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c \
D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c \
D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.d \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.d \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o \
./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o: D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c_includes.args"
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o: D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c_includes.args"
Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o: D:/GIT_WorkAreas/eSTAR_InstrumentCluster/eStar_Cluster_Demo/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c Drivers/BSP/STM32H735G-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c_includes.args"

clean: clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK

clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK:
	-$(RM) ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.su ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.su ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.cyclo ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.d ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.o ./Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H735G-2d-DK

