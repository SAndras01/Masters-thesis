################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f446retx.s 

S_DEPS += \
./Core/Startup/startup_stm32f446retx.d 

OBJS += \
./Core/Startup/startup_stm32f446retx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/ICM2098" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f446retx.d ./Core/Startup/startup_stm32f446retx.o

.PHONY: clean-Core-2f-Startup

