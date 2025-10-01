################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Commander-API-3.0.0/src/Commander-API.cpp \
../Drivers/Commander-API-3.0.0/src/Commander-Arguments.cpp \
../Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.cpp \
../Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.cpp \
../Drivers/Commander-API-3.0.0/src/Commander-IO.cpp 

OBJS += \
./Drivers/Commander-API-3.0.0/src/Commander-API.o \
./Drivers/Commander-API-3.0.0/src/Commander-Arguments.o \
./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.o \
./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.o \
./Drivers/Commander-API-3.0.0/src/Commander-IO.o 

CPP_DEPS += \
./Drivers/Commander-API-3.0.0/src/Commander-API.d \
./Drivers/Commander-API-3.0.0/src/Commander-Arguments.d \
./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.d \
./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.d \
./Drivers/Commander-API-3.0.0/src/Commander-IO.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Commander-API-3.0.0/src/%.o Drivers/Commander-API-3.0.0/src/%.su Drivers/Commander-API-3.0.0/src/%.cyclo: ../Drivers/Commander-API-3.0.0/src/%.cpp Drivers/Commander-API-3.0.0/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Commander-2d-API-2d-3-2e-0-2e-0-2f-src

clean-Drivers-2f-Commander-2d-API-2d-3-2e-0-2e-0-2f-src:
	-$(RM) ./Drivers/Commander-API-3.0.0/src/Commander-API.cyclo ./Drivers/Commander-API-3.0.0/src/Commander-API.d ./Drivers/Commander-API-3.0.0/src/Commander-API.o ./Drivers/Commander-API-3.0.0/src/Commander-API.su ./Drivers/Commander-API-3.0.0/src/Commander-Arguments.cyclo ./Drivers/Commander-API-3.0.0/src/Commander-Arguments.d ./Drivers/Commander-API-3.0.0/src/Commander-Arguments.o ./Drivers/Commander-API-3.0.0/src/Commander-Arguments.su ./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.cyclo ./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.d ./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.o ./Drivers/Commander-API-3.0.0/src/Commander-Autocomplete.su ./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.cyclo ./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.d ./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.o ./Drivers/Commander-API-3.0.0/src/Commander-Caller-Interface.su ./Drivers/Commander-API-3.0.0/src/Commander-IO.cyclo ./Drivers/Commander-API-3.0.0/src/Commander-IO.d ./Drivers/Commander-API-3.0.0/src/Commander-IO.o ./Drivers/Commander-API-3.0.0/src/Commander-IO.su

.PHONY: clean-Drivers-2f-Commander-2d-API-2d-3-2e-0-2e-0-2f-src

