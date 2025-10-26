################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/Numpad/numpad.cpp 

OBJS += \
./Core/Modules/Numpad/numpad.o 

CPP_DEPS += \
./Core/Modules/Numpad/numpad.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/Numpad/%.o Core/Modules/Numpad/%.su Core/Modules/Numpad/%.cyclo: ../Core/Modules/Numpad/%.cpp Core/Modules/Numpad/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/ICM2098" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-Numpad

clean-Core-2f-Modules-2f-Numpad:
	-$(RM) ./Core/Modules/Numpad/numpad.cyclo ./Core/Modules/Numpad/numpad.d ./Core/Modules/Numpad/numpad.o ./Core/Modules/Numpad/numpad.su

.PHONY: clean-Core-2f-Modules-2f-Numpad

