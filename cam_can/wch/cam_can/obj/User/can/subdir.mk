################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/can/app_can_cmds.c \
../User/can/cam_can_drv.c \
../User/can/can_thr.c 

OBJS += \
./User/can/app_can_cmds.o \
./User/can/cam_can_drv.o \
./User/can/can_thr.o 

C_DEPS += \
./User/can/app_can_cmds.d \
./User/can/cam_can_drv.d \
./User/can/can_thr.d 


# Each subdirectory must supply rules for building sources it contributes
User/can/%.o: ../User/can/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\common\can" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\MemMang" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\can" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

