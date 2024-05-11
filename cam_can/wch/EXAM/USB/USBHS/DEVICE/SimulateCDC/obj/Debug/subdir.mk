################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/proj/velograph/snail_w/cam_can/wch/EXAM/SRC/Debug/_debug.c \
D:/proj/velograph/snail_w/cam_can/wch/EXAM/SRC/Debug/debug.c 

OBJS += \
./Debug/_debug.o \
./Debug/debug.o 

C_DEPS += \
./Debug/_debug.d \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/_debug.o: D:/proj/velograph/snail_w/cam_can/wch/EXAM/SRC/Debug/_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\UART" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Debug/debug.o: D:/proj/velograph/snail_w/cam_can/wch/EXAM/SRC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\UART" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\USB\USBHS\DEVICE\SimulateCDC\User" -I"D:\proj\velograph\snail_w\cam_can\wch\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

