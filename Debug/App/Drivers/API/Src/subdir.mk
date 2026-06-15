################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Drivers/API/Src/driver_can.c \
../App/Drivers/API/Src/motor.c \
../App/Drivers/API/Src/sensor.c 

OBJS += \
./App/Drivers/API/Src/driver_can.o \
./App/Drivers/API/Src/motor.o \
./App/Drivers/API/Src/sensor.o 

C_DEPS += \
./App/Drivers/API/Src/driver_can.d \
./App/Drivers/API/Src/motor.d \
./App/Drivers/API/Src/sensor.d 


# Each subdirectory must supply rules for building sources it contributes
App/Drivers/API/Src/%.o App/Drivers/API/Src/%.su App/Drivers/API/Src/%.cyclo: ../App/Drivers/API/Src/%.c App/Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/STM32_workspace/target_tracker/App/Algorithm/Inc" -I"C:/STM32_workspace/target_tracker/App" -I"C:/STM32_workspace/target_tracker/App/Drivers/API/Inc" -I"C:/STM32_workspace/target_tracker/App/Drivers/ll_API/Inc" -I"C:/STM32_workspace/target_tracker/App/Tasks/Inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/include" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/STM32_workspace/target_tracker/ThirdParty/FreeRTOS/portable/MemMang" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Drivers-2f-API-2f-Src

clean-App-2f-Drivers-2f-API-2f-Src:
	-$(RM) ./App/Drivers/API/Src/driver_can.cyclo ./App/Drivers/API/Src/driver_can.d ./App/Drivers/API/Src/driver_can.o ./App/Drivers/API/Src/driver_can.su ./App/Drivers/API/Src/motor.cyclo ./App/Drivers/API/Src/motor.d ./App/Drivers/API/Src/motor.o ./App/Drivers/API/Src/motor.su ./App/Drivers/API/Src/sensor.cyclo ./App/Drivers/API/Src/sensor.d ./App/Drivers/API/Src/sensor.o ./App/Drivers/API/Src/sensor.su

.PHONY: clean-App-2f-Drivers-2f-API-2f-Src

