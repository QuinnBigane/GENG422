################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l152xe.s 

OBJS += \
./startup/startup_stm32l152xe.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/core" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/device" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/Utilities/STM32L1xx_Nucleo" -I"C:/Directory/geng422/DevelopmentSystem/Session24/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


