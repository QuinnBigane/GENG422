################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clock.c \
../src/dbg.c \
../src/eprintf.c \
../src/main.c \
../src/stm32l1xx_it.c \
../src/syscalls.c \
../src/system_stm32l1xx.c \
../src/uart.c 

OBJS += \
./src/clock.o \
./src/dbg.o \
./src/eprintf.o \
./src/main.o \
./src/stm32l1xx_it.o \
./src/syscalls.o \
./src/system_stm32l1xx.o \
./src/uart.o 

C_DEPS += \
./src/clock.d \
./src/dbg.d \
./src/eprintf.d \
./src/main.d \
./src/stm32l1xx_it.d \
./src/syscalls.d \
./src/system_stm32l1xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RETx -DNUCLEO_L152RE -DDEBUG -DSTM32L152xE -DUSE_HAL_DRIVER -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/core" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/CMSIS/device" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/HAL_Driver/Inc" -I"C:/Directory/geng422/DevelopmentSystem/nucleo-l152re_hal_lib/Utilities/STM32L1xx_Nucleo" -I"C:/Directory/geng422/DevelopmentSystem/Session24/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


