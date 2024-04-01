################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/brd/cam_can_brd.c 

OBJS += \
./User/brd/cam_can_brd.o 

C_DEPS += \
./User/brd/cam_can_brd.d 


# Each subdirectory must supply rules for building sources it contributes
User/brd/%.o: ../User/brd/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\UART" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

