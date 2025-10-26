################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f767zitx.s 

S_DEPS += \
./Core/Startup/startup_stm32f767zitx.d 

OBJS += \
./Core/Startup/startup_stm32f767zitx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GPIO" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StepperController" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Numpad" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/SSD1305" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/ICM2098" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/AS5147U" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Memory" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/StateMachine" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/GUI" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Stream" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Serial" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/TwoAxisPlatformMain/Core/Modules/Accelerometer" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f767zitx.d ./Core/Startup/startup_stm32f767zitx.o

.PHONY: clean-Core-2f-Startup

