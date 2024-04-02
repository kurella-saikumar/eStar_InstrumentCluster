################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SwitchInf.c 

C_DEPS += \
./SwitchInf.d 

OBJS += \
./SwitchInf.o 


# Each subdirectory must supply rules for building sources it contributes
%.o %.su %.cyclo: ../%.c subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch_Handler" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/Switch" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/APP/DriverInfoApplication" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/APP/Clock_App" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/GITWORKAREA/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/Switch_Interface" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean--2e-

clean--2e-:
	-$(RM) ./SwitchInf.cyclo ./SwitchInf.d ./SwitchInf.o ./SwitchInf.su

.PHONY: clean--2e-

