################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/pabllo/MEGA/POS_GRADUACAO_SENAI/Sistemas_embarcados/Projetos_Pos_Sistemas_Embarcados/Semestre_1/PROEMB/CubeIDEWorkspace/GPIO_IOToggle/Src/main.c \
/home/pabllo/MEGA/POS_GRADUACAO_SENAI/Sistemas_embarcados/Projetos_Pos_Sistemas_Embarcados/Semestre_1/PROEMB/CubeIDEWorkspace/GPIO_IOToggle/Src/stm32f4xx_it.c 

OBJS += \
./Example/User/main.o \
./Example/User/stm32f4xx_it.o 

C_DEPS += \
./Example/User/main.d \
./Example/User/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Example/User/main.o: /home/pabllo/MEGA/POS_GRADUACAO_SENAI/Sistemas_embarcados/Projetos_Pos_Sistemas_Embarcados/Semestre_1/PROEMB/CubeIDEWorkspace/GPIO_IOToggle/Src/main.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_STM32F4XX_NUCLEO -DUSE_IOEXPANDER -DSTM32F446xx -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/BSP/STM32F4xx-Nucleo -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Example/User/stm32f4xx_it.o: /home/pabllo/MEGA/POS_GRADUACAO_SENAI/Sistemas_embarcados/Projetos_Pos_Sistemas_Embarcados/Semestre_1/PROEMB/CubeIDEWorkspace/GPIO_IOToggle/Src/stm32f4xx_it.c Example/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_STM32F4XX_NUCLEO -DUSE_IOEXPANDER -DSTM32F446xx -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/BSP/STM32F4xx-Nucleo -I../../../Drivers/BSP/Components/Common -I../../../Utilities/Log -I../../../Utilities/Fonts -I../../../Utilities/CPU -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Example-2f-User

clean-Example-2f-User:
	-$(RM) ./Example/User/main.d ./Example/User/main.o ./Example/User/main.su ./Example/User/stm32f4xx_it.d ./Example/User/stm32f4xx_it.o ./Example/User/stm32f4xx_it.su

.PHONY: clean-Example-2f-User

