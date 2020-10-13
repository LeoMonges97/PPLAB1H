################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PPLAB1H\ -\ Leonel.c 

OBJS += \
./src/PPLAB1H\ -\ Leonel.o 

C_DEPS += \
./src/PPLAB1H\ -\ Leonel.d 


# Each subdirectory must supply rules for building sources it contributes
src/PPLAB1H\ -\ Leonel.o: ../src/PPLAB1H\ -\ Leonel.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/PPLAB1H - Leonel.d" -MT"src/PPLAB1H\ -\ Leonel.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


