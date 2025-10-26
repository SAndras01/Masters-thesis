################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/StateMachine/state_machine.cpp 

OBJS += \
./Core/Modules/StateMachine/state_machine.o 

CPP_DEPS += \
./Core/Modules/StateMachine/state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/StateMachine/%.o Core/Modules/StateMachine/%.su Core/Modules/StateMachine/%.cyclo: ../Core/Modules/StateMachine/%.cpp Core/Modules/StateMachine/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GPIO" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StepperController" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Numpad" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/SSD1305" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/ICM2098" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/AS5147U" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Memory" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StateMachine" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GUI" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Stream" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Serial" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Accelerometer" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-StateMachine

clean-Core-2f-Modules-2f-StateMachine:
	-$(RM) ./Core/Modules/StateMachine/state_machine.cyclo ./Core/Modules/StateMachine/state_machine.d ./Core/Modules/StateMachine/state_machine.o ./Core/Modules/StateMachine/state_machine.su

.PHONY: clean-Core-2f-Modules-2f-StateMachine

