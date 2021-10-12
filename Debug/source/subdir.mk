################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Buffahiti.c \
../source/button.c \
../source/led_on.c \
../source/mtb.c \
../source/pwm.c \
../source/semihost_hardfault.c \
../source/state_machine.c \
../source/systick.c \
../source/touch.c 

OBJS += \
./source/Buffahiti.o \
./source/button.o \
./source/led_on.o \
./source/mtb.o \
./source/pwm.o \
./source/semihost_hardfault.o \
./source/state_machine.o \
./source/systick.o \
./source/touch.o 

C_DEPS += \
./source/Buffahiti.d \
./source/button.d \
./source/led_on.d \
./source/mtb.d \
./source/pwm.d \
./source/semihost_hardfault.d \
./source/state_machine.d \
./source/systick.d \
./source/touch.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\board" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\source" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\drivers" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\CMSIS" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\utilities" -I"C:\Users\ACER\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Assignments\Buffahiti\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


