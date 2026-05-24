################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LF/LF.c 

OBJS += \
./Core/LF/LF.o 

C_DEPS += \
./Core/LF/LF.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LF/%.o Core/LF/%.su Core/LF/%.cyclo: ../Core/LF/%.c Core/LF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pakal/Desktop/VeA/Personal/Line_Follower/line-follower/Line_Follower_CODE/LINE_FOLLOWER/Core/LF" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LF

clean-Core-2f-LF:
	-$(RM) ./Core/LF/LF.cyclo ./Core/LF/LF.d ./Core/LF/LF.o ./Core/LF/LF.su

.PHONY: clean-Core-2f-LF

