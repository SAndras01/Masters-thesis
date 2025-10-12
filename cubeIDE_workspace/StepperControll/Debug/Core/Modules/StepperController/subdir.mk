################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Modules/StepperController/StepperController.cpp 

OBJS += \
./Core/Modules/StepperController/StepperController.o 

CPP_DEPS += \
./Core/Modules/StepperController/StepperController.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Modules/StepperController/%.o Core/Modules/StepperController/%.su Core/Modules/StepperController/%.cyclo: ../Core/Modules/StepperController/%.cpp Core/Modules/StepperController/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StepperControll/Core/Modules" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StepperControll/Core/Modules/GPIO" -I"D:/Projektek/Masters-thesis/cubeIDE_workspace/StepperControll/Core/Modules/StepperController" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Modules-2f-StepperController

clean-Core-2f-Modules-2f-StepperController:
	-$(RM) ./Core/Modules/StepperController/StepperController.cyclo ./Core/Modules/StepperController/StepperController.d ./Core/Modules/StepperController/StepperController.o ./Core/Modules/StepperController/StepperController.su

.PHONY: clean-Core-2f-Modules-2f-StepperController

