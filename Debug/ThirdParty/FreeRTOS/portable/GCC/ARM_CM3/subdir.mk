################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.c 

OBJS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/%.o ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/%.su ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/%.cyclo: ../ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/%.c ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/STM32_workspace/target_tracker/App/Algorithm/Inc" -I"C:/STM32_workspace/target_tracker/App" -I"C:/STM32_workspace/target_tracker/App/Drivers/API/Inc" -I"C:/STM32_workspace/target_tracker/App/Drivers/ll_API/Inc" -I"C:/STM32_workspace/target_tracker/App/Tasks/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/include" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/MemMang" -I"C:/STM32_workspace/target_tracker/ThirdParty/SEGGER_SYSTEMVIEW/Config" -I"C:/STM32_workspace/target_tracker/ThirdParty/SEGGER_SYSTEMVIEW/OS" -I"C:/STM32_workspace/target_tracker/ThirdParty/SEGGER_SYSTEMVIEW/SEGGER" -I"C:/STM32_workspace/target_tracker/ThirdParty/SEGGER_SYSTEMVIEW/SYSVIEW" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3

clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.cyclo ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.d ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.o ./ThirdParty/FreeRTOS/portable/GCC/ARM_CM3/port.su

.PHONY: clean-ThirdParty-2f-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3

