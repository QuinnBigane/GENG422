################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32L1xx_Nucleo/stm32l1xx_nucleo.c 

OBJS += \
./Utilities/STM32L1xx_Nucleo/stm32l1xx_nucleo.o 

C_DEPS += \
./Utilities/STM32L1xx_Nucleo/stm32l1xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32L1xx_Nucleo/%.o: ../Utilities/STM32L1xx_Nucleo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32L152xE -DUSE_HAL_DRIVER -DDEBUG -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/Utilities/STM32L1xx_Nucleo" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/device" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/core" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


