################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/StepperController/StepperController.cpp 

OBJS += \
./Core/Modules/StepperController/StepperController.o 

CPP_DEPS += \
./Core/Modules/StepperController/StepperController.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/StepperController/%.o Core/Modules/StepperController/%.su Core/Modules/StepperController/%.cyclo: ../Core/Modules/StepperController/%.cpp Core/Modules/StepperController/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GPIO" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StepperController" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/ICM2098" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/AS5147U" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Accelerometer" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-StepperController

clean-Core-2f-Modules-2f-StepperController:
	-$(RM) ./Core/Modules/StepperController/StepperController.cyclo ./Core/Modules/StepperController/StepperController.d ./Core/Modules/StepperController/StepperController.o ./Core/Modules/StepperController/StepperController.su

.PHONY: clean-Core-2f-Modules-2f-StepperController

