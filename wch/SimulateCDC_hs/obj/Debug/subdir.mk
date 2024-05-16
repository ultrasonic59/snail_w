################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: D:/proj/velograph/snail_w/wch/SimulateCDC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\SimulateCDC\User\UART" -I"D:\proj\velograph\snail_w\wch\SimulateCDC\User\USB_Device" -I"D:\proj\velograph\snail_w\wch\SimulateCDC\Debug" -I"D:\proj\velograph\snail_w\wch\SimulateCDC\Core" -I"D:\proj\velograph\snail_w\wch\SimulateCDC\User" -I"D:\proj\velograph\snail_w\wch\SimulateCDC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

