################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/Stream/Print.cpp \
../Core/Modules/Stream/Stream.cpp \
../Core/Modules/Stream/System.cpp 

OBJS += \
./Core/Modules/Stream/Print.o \
./Core/Modules/Stream/Stream.o \
./Core/Modules/Stream/System.o 

CPP_DEPS += \
./Core/Modules/Stream/Print.d \
./Core/Modules/Stream/Stream.d \
./Core/Modules/Stream/System.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/Stream/%.o Core/Modules/Stream/%.su Core/Modules/Stream/%.cyclo: ../Core/Modules/Stream/%.cpp Core/Modules/Stream/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/StateMachine" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/GUI" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Memory" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Accelerometer" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Numpad" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/Stream" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-Stream

clean-Core-2f-Modules-2f-Stream:
	-$(RM) ./Core/Modules/Stream/Print.cyclo ./Core/Modules/Stream/Print.d ./Core/Modules/Stream/Print.o ./Core/Modules/Stream/Print.su ./Core/Modules/Stream/Stream.cyclo ./Core/Modules/Stream/Stream.d ./Core/Modules/Stream/Stream.o ./Core/Modules/Stream/Stream.su ./Core/Modules/Stream/System.cyclo ./Core/Modules/Stream/System.d ./Core/Modules/Stream/System.o ./Core/Modules/Stream/System.su

.PHONY: clean-Core-2f-Modules-2f-Stream

