################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/drv_gpio.c \
../drivers/drv_usart.c \
../drivers/lcd.c 

OBJS += \
./drivers/drv_gpio.o \
./drivers/drv_usart.o \
./drivers/lcd.o 

C_DEPS += \
./drivers/drv_gpio.d \
./drivers/drv_usart.d \
./drivers/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\drivers" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include\libc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\misc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\serial" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

