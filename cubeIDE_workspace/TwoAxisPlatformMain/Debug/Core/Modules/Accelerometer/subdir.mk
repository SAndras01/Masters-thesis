################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/Accelerometer/accelerometer.cpp 

OBJS += \
./Core/Modules/Accelerometer/accelerometer.o 

CPP_DEPS += \
./Core/Modules/Accelerometer/accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/Accelerometer/%.o Core/Modules/Accelerometer/%.su Core/Modules/Accelerometer/%.cyclo: ../Core/Modules/Accelerometer/%.cpp Core/Modules/Accelerometer/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GPIO" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StepperController" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Numpad" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/SSD1305" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/ICM2098" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/AS5147U" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Memory" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StateMachine" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GUI" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Stream" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Serial" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Accelerometer" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-Accelerometer

clean-Core-2f-Modules-2f-Accelerometer:
	-$(RM) ./Core/Modules/Accelerometer/accelerometer.cyclo ./Core/Modules/Accelerometer/accelerometer.d ./Core/Modules/Accelerometer/accelerometer.o ./Core/Modules/Accelerometer/accelerometer.su

.PHONY: clean-Core-2f-Modules-2f-Accelerometer

