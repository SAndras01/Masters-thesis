################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
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
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-Numpad

clean-Core-2f-Modules-2f-Numpad:
	-$(RM) ./Core/Modules/Numpad/numpad.cyclo ./Core/Modules/Numpad/numpad.d ./Core/Modules/Numpad/numpad.o ./Core/Modules/Numpad/numpad.su

.PHONY: clean-Core-2f-Modules-2f-Numpad

