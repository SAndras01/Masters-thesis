################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/GUI/GUI_demo.cpp 

OBJS += \
./Core/Modules/GUI/GUI_demo.o 

CPP_DEPS += \
./Core/Modules/GUI/GUI_demo.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/GUI/%.o Core/Modules/GUI/%.su Core/Modules/GUI/%.cyclo: ../Core/Modules/GUI/%.cpp Core/Modules/GUI/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/OLED/Core/Modules/SSD1306" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/OLED/Core/Modules/SSD1305" -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/OLED/Core/Modules/GUI" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-GUI

clean-Core-2f-Modules-2f-GUI:
	-$(RM) ./Core/Modules/GUI/GUI_demo.cyclo ./Core/Modules/GUI/GUI_demo.d ./Core/Modules/GUI/GUI_demo.o ./Core/Modules/GUI/GUI_demo.su

.PHONY: clean-Core-2f-Modules-2f-GUI

