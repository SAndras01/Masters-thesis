################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Modules/SSD1305/fonts.c 

CPP_SRCS += \
../Core/Modules/SSD1305/SSD1305.cpp 

C_DEPS += \
./Core/Modules/SSD1305/fonts.d 

OBJS += \
./Core/Modules/SSD1305/SSD1305.o \
./Core/Modules/SSD1305/fonts.o 

CPP_DEPS += \
./Core/Modules/SSD1305/SSD1305.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/SSD1305/%.o Core/Modules/SSD1305/%.su Core/Modules/SSD1305/%.cyclo: ../Core/Modules/SSD1305/%.cpp Core/Modules/SSD1305/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Modules/SSD1305/%.o Core/Modules/SSD1305/%.su Core/Modules/SSD1305/%.cyclo: ../Core/Modules/SSD1305/%.c Core/Modules/SSD1305/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/SNA1BP/Documents/Masters-thesis/cubeIDE_workspace/StateMachine/Core/Modules/SSD1305" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-SSD1305

clean-Core-2f-Modules-2f-SSD1305:
	-$(RM) ./Core/Modules/SSD1305/SSD1305.cyclo ./Core/Modules/SSD1305/SSD1305.d ./Core/Modules/SSD1305/SSD1305.o ./Core/Modules/SSD1305/SSD1305.su ./Core/Modules/SSD1305/fonts.cyclo ./Core/Modules/SSD1305/fonts.d ./Core/Modules/SSD1305/fonts.o ./Core/Modules/SSD1305/fonts.su

.PHONY: clean-Core-2f-Modules-2f-SSD1305

