################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/src/Service/System_Service/checksum/checksum.c 

C_DEPS += \
./Application/User/Core/src/Service/System_Service/checksum/checksum.d 

OBJS += \
./Application/User/Core/src/Service/System_Service/checksum/checksum.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/src/Service/System_Service/checksum/%.o Application/User/Core/src/Service/System_Service/checksum/%.su Application/User/Core/src/Service/System_Service/checksum/%.cyclo: ../Application/User/Core/src/Service/System_Service/checksum/%.c Application/User/Core/src/Service/System_Service/checksum/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=24 -DDEBUG -DSTM32H735xx -c -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/DigitalDebounce" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/Memory_Service/eeprom_emul/eeprom_emulation" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/Memory_Service/eeprom_emul/flash_interface" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/checksum" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/ECUPwrMode_SmApp" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/IgnitionManager" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/System_Service/stateManager" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/PlatformConfig" -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/STM32H735G-DK -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/App/Odometer_App" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/App/Speedometer_App" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/App/Tachometer_App" -I"D:/GIT_WorkAreas/eSTAR_InstrumentCluster/STM32CubeIDE/Application/User/Core/src/Service/IO_HAL/ICU_middleware" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-checksum

clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-checksum:
	-$(RM) ./Application/User/Core/src/Service/System_Service/checksum/checksum.cyclo ./Application/User/Core/src/Service/System_Service/checksum/checksum.d ./Application/User/Core/src/Service/System_Service/checksum/checksum.o ./Application/User/Core/src/Service/System_Service/checksum/checksum.su

.PHONY: clean-Application-2f-User-2f-Core-2f-src-2f-Service-2f-System_Service-2f-checksum

