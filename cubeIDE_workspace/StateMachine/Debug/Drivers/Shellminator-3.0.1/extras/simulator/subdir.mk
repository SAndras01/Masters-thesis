################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Shellminator-3.0.1/extras/simulator/Print.cpp \
../Drivers/Shellminator-3.0.1/extras/simulator/Stream.cpp \
../Drivers/Shellminator-3.0.1/extras/simulator/System.cpp \
../Drivers/Shellminator-3.0.1/extras/simulator/simulator.cpp \
../Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.cpp 

OBJS += \
./Drivers/Shellminator-3.0.1/extras/simulator/Print.o \
./Drivers/Shellminator-3.0.1/extras/simulator/Stream.o \
./Drivers/Shellminator-3.0.1/extras/simulator/System.o \
./Drivers/Shellminator-3.0.1/extras/simulator/simulator.o \
./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.o 

CPP_DEPS += \
./Drivers/Shellminator-3.0.1/extras/simulator/Print.d \
./Drivers/Shellminator-3.0.1/extras/simulator/Stream.d \
./Drivers/Shellminator-3.0.1/extras/simulator/System.d \
./Drivers/Shellminator-3.0.1/extras/simulator/simulator.d \
./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Shellminator-3.0.1/extras/simulator/%.o Drivers/Shellminator-3.0.1/extras/simulator/%.su Drivers/Shellminator-3.0.1/extras/simulator/%.cyclo: ../Drivers/Shellminator-3.0.1/extras/simulator/%.cpp Drivers/Shellminator-3.0.1/extras/simulator/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-extras-2f-simulator

clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-extras-2f-simulator:
	-$(RM) ./Drivers/Shellminator-3.0.1/extras/simulator/Print.cyclo ./Drivers/Shellminator-3.0.1/extras/simulator/Print.d ./Drivers/Shellminator-3.0.1/extras/simulator/Print.o ./Drivers/Shellminator-3.0.1/extras/simulator/Print.su ./Drivers/Shellminator-3.0.1/extras/simulator/Stream.cyclo ./Drivers/Shellminator-3.0.1/extras/simulator/Stream.d ./Drivers/Shellminator-3.0.1/extras/simulator/Stream.o ./Drivers/Shellminator-3.0.1/extras/simulator/Stream.su ./Drivers/Shellminator-3.0.1/extras/simulator/System.cyclo ./Drivers/Shellminator-3.0.1/extras/simulator/System.d ./Drivers/Shellminator-3.0.1/extras/simulator/System.o ./Drivers/Shellminator-3.0.1/extras/simulator/System.su ./Drivers/Shellminator-3.0.1/extras/simulator/simulator.cyclo ./Drivers/Shellminator-3.0.1/extras/simulator/simulator.d ./Drivers/Shellminator-3.0.1/extras/simulator/simulator.o ./Drivers/Shellminator-3.0.1/extras/simulator/simulator.su ./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.cyclo ./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.d ./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.o ./Drivers/Shellminator-3.0.1/extras/simulator/stdioStream.su

.PHONY: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-extras-2f-simulator

