################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Main.c \
../User/ch32v20x_it.c \
../User/system_ch32v20x.c 

OBJS += \
./User/Main.o \
./User/ch32v20x_it.o \
./User/system_ch32v20x.o 

C_DEPS += \
./User/Main.d \
./User/ch32v20x_it.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\USBLIB\CONFIG" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\USBLIB\USB-Driver\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\UART" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

