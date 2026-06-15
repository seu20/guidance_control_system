################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Tasks/Src/control_task.c \
../App/Tasks/Src/sensor_task.c \
../App/Tasks/Src/uart_task.c 

OBJS += \
./App/Tasks/Src/control_task.o \
./App/Tasks/Src/sensor_task.o \
./App/Tasks/Src/uart_task.o 

C_DEPS += \
./App/Tasks/Src/control_task.d \
./App/Tasks/Src/sensor_task.d \
./App/Tasks/Src/uart_task.d 


# Each subdirectory must supply rules for building sources it contributes
App/Tasks/Src/%.o App/Tasks/Src/%.su App/Tasks/Src/%.cyclo: ../App/Tasks/Src/%.c App/Tasks/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/STM32_workspace/target_tracker/App/Algorithm/Inc" -I"C:/STM32_workspace/target_tracker/App" -I"C:/STM32_workspace/target_tracker/App/Drivers/API/Inc" -I"C:/STM32_workspace/target_tracker/App/Drivers/ll_API/Inc" -I"C:/STM32_workspace/target_tracker/App/Tasks/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/include" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/MemMang" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Tasks-2f-Src

clean-App-2f-Tasks-2f-Src:
	-$(RM) ./App/Tasks/Src/control_task.cyclo ./App/Tasks/Src/control_task.d ./App/Tasks/Src/control_task.o ./App/Tasks/Src/control_task.su ./App/Tasks/Src/sensor_task.cyclo ./App/Tasks/Src/sensor_task.d ./App/Tasks/Src/sensor_task.o ./App/Tasks/Src/sensor_task.su ./App/Tasks/Src/uart_task.cyclo ./App/Tasks/Src/uart_task.d ./App/Tasks/Src/uart_task.o ./App/Tasks/Src/uart_task.su

.PHONY: clean-App-2f-Tasks-2f-Src

