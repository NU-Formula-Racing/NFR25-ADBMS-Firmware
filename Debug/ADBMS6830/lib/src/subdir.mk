################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Analog\ Devices/ADBMS6830_Free_Source_Code-Rel1.0.1/Other_Workbench/ADBMS6830/lib/src/adBms6830GenericType.c \
C:/Analog\ Devices/ADBMS6830_Free_Source_Code-Rel1.0.1/Other_Workbench/ADBMS6830/lib/src/adBms6830ParseCreate.c 

OBJS += \
./ADBMS6830/lib/src/adBms6830GenericType.o \
./ADBMS6830/lib/src/adBms6830ParseCreate.o 

C_DEPS += \
./ADBMS6830/lib/src/adBms6830GenericType.d \
./ADBMS6830/lib/src/adBms6830ParseCreate.d 


# Each subdirectory must supply rules for building sources it contributes
ADBMS6830/lib/src/adBms6830GenericType.o: C:/Analog\ Devices/ADBMS6830_Free_Source_Code-Rel1.0.1/Other_Workbench/ADBMS6830/lib/src/adBms6830GenericType.c ADBMS6830/lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../ADBMS6830/lib/inc -I../ADBMS6830/program/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ADBMS6830/lib/src/adBms6830ParseCreate.o: C:/Analog\ Devices/ADBMS6830_Free_Source_Code-Rel1.0.1/Other_Workbench/ADBMS6830/lib/src/adBms6830ParseCreate.c ADBMS6830/lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../ADBMS6830/lib/inc -I../ADBMS6830/program/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ADBMS6830-2f-lib-2f-src

clean-ADBMS6830-2f-lib-2f-src:
	-$(RM) ./ADBMS6830/lib/src/adBms6830GenericType.cyclo ./ADBMS6830/lib/src/adBms6830GenericType.d ./ADBMS6830/lib/src/adBms6830GenericType.o ./ADBMS6830/lib/src/adBms6830GenericType.su ./ADBMS6830/lib/src/adBms6830ParseCreate.cyclo ./ADBMS6830/lib/src/adBms6830ParseCreate.d ./ADBMS6830/lib/src/adBms6830ParseCreate.o ./ADBMS6830/lib/src/adBms6830ParseCreate.su

.PHONY: clean-ADBMS6830-2f-lib-2f-src

