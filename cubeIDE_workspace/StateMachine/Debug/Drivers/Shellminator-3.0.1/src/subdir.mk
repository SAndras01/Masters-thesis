################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Events.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Input.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Styles.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.cpp \
../Drivers/Shellminator-3.0.1/src/Shellminator.cpp 

OBJS += \
./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Events.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Input.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.o \
./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.o \
./Drivers/Shellminator-3.0.1/src/Shellminator.o 

CPP_DEPS += \
./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Events.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Input.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.d \
./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.d \
./Drivers/Shellminator-3.0.1/src/Shellminator.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Shellminator-3.0.1/src/%.o Drivers/Shellminator-3.0.1/src/%.su Drivers/Shellminator-3.0.1/src/%.cyclo: ../Drivers/Shellminator-3.0.1/src/%.cpp Drivers/Shellminator-3.0.1/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src

clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src:
	-$(RM) ./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.d ./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.o ./Drivers/Shellminator-3.0.1/src/Shellminator-BLE-Stream.su ./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.d ./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.o ./Drivers/Shellminator-3.0.1/src/Shellminator-BufferedPrinter.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Colorizer.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Commander-Interface.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Crypto.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Events.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Events.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Events.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Events.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Helpers.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Input.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Input.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Input.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Input.su ./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.d ./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.o ./Drivers/Shellminator-3.0.1/src/Shellminator-MouseInterface.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Neofetch.su ./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.d ./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.o ./Drivers/Shellminator-3.0.1/src/Shellminator-QR-Code-Module.su ./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.d ./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.o ./Drivers/Shellminator-3.0.1/src/Shellminator-SearchModule.su ./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.d ./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.o ./Drivers/Shellminator-3.0.1/src/Shellminator-SpecialKeys.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Styles.su ./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.d ./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.o ./Drivers/Shellminator-3.0.1/src/Shellminator-TcpSocket.su ./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.d ./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.o ./Drivers/Shellminator-3.0.1/src/Shellminator-WebServer.su ./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.d ./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.o ./Drivers/Shellminator-3.0.1/src/Shellminator-Websocket.su ./Drivers/Shellminator-3.0.1/src/Shellminator.cyclo ./Drivers/Shellminator-3.0.1/src/Shellminator.d ./Drivers/Shellminator-3.0.1/src/Shellminator.o ./Drivers/Shellminator-3.0.1/src/Shellminator.su

.PHONY: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src

