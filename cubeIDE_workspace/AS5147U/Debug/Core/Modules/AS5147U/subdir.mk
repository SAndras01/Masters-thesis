################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/AS5147U/AS5147U.cpp 

OBJS += \
./Core/Modules/AS5147U/AS5147U.o 

CPP_DEPS += \
./Core/Modules/AS5147U/AS5147U.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/AS5147U/%.o Core/Modules/AS5147U/%.su Core/Modules/AS5147U/%.cyclo: ../Core/Modules/AS5147U/%.cpp Core/Modules/AS5147U/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/AS5147U/Core/Modules/AS5147U" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/AS5147U/Core/Modules/GPIO" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-AS5147U

clean-Core-2f-Modules-2f-AS5147U:
	-$(RM) ./Core/Modules/AS5147U/AS5147U.cyclo ./Core/Modules/AS5147U/AS5147U.d ./Core/Modules/AS5147U/AS5147U.o ./Core/Modules/AS5147U/AS5147U.su

.PHONY: clean-Core-2f-Modules-2f-AS5147U

