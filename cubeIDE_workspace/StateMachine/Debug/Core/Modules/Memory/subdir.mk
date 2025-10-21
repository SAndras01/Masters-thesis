################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/Memory/memory.cpp \
../Core/Modules/Memory/memorySlot.cpp 

OBJS += \
./Core/Modules/Memory/memory.o \
./Core/Modules/Memory/memorySlot.o 

CPP_DEPS += \
./Core/Modules/Memory/memory.d \
./Core/Modules/Memory/memorySlot.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/Memory/%.o Core/Modules/Memory/%.su Core/Modules/Memory/%.cyclo: ../Core/Modules/Memory/%.cpp Core/Modules/Memory/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/ICM2098" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-Memory

clean-Core-2f-Modules-2f-Memory:
	-$(RM) ./Core/Modules/Memory/memory.cyclo ./Core/Modules/Memory/memory.d ./Core/Modules/Memory/memory.o ./Core/Modules/Memory/memory.su ./Core/Modules/Memory/memorySlot.cyclo ./Core/Modules/Memory/memorySlot.d ./Core/Modules/Memory/memorySlot.o ./Core/Modules/Memory/memorySlot.su

.PHONY: clean-Core-2f-Modules-2f-Memory

