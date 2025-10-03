################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.cpp \
../Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.cpp 

OBJS += \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.o \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.o 

CPP_DEPS += \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.d \
./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Shellminator-3.0.1/src/GUI/%.o Drivers/Shellminator-3.0.1/src/GUI/%.su Drivers/Shellminator-3.0.1/src/GUI/%.cyclo: ../Drivers/Shellminator-3.0.1/src/GUI/%.cpp Drivers/Shellminator-3.0.1/src/GUI/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Serial" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Shellminator-3.0.1/src" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StateMachine/Drivers/Commander-API-3.0.0" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src-2f-GUI

clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src-2f-GUI:
	-$(RM) ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Buttons.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Level-Meter.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List-Detailed.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-List.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Notification.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-PlotModule.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-Progress.su ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.cyclo ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.d ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.o ./Drivers/Shellminator-3.0.1/src/GUI/Shellminator-ScreenGrid.su

.PHONY: clean-Drivers-2f-Shellminator-2d-3-2e-0-2e-1-2f-src-2f-GUI

