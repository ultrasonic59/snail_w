################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/USBLIB/CONFIG/hw_config.c \
../User/USBLIB/CONFIG/usb_desc.c \
../User/USBLIB/CONFIG/usb_endp.c \
../User/USBLIB/CONFIG/usb_istr.c \
../User/USBLIB/CONFIG/usb_prop.c \
../User/USBLIB/CONFIG/usb_pwr.c 

OBJS += \
./User/USBLIB/CONFIG/hw_config.o \
./User/USBLIB/CONFIG/usb_desc.o \
./User/USBLIB/CONFIG/usb_endp.o \
./User/USBLIB/CONFIG/usb_istr.o \
./User/USBLIB/CONFIG/usb_prop.o \
./User/USBLIB/CONFIG/usb_pwr.o 

C_DEPS += \
./User/USBLIB/CONFIG/hw_config.d \
./User/USBLIB/CONFIG/usb_desc.d \
./User/USBLIB/CONFIG/usb_endp.d \
./User/USBLIB/CONFIG/usb_istr.d \
./User/USBLIB/CONFIG/usb_prop.d \
./User/USBLIB/CONFIG/usb_pwr.d 


# Each subdirectory must supply rules for building sources it contributes
User/USBLIB/CONFIG/%.o: ../User/USBLIB/CONFIG/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\USBLIB\CONFIG" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\USBLIB\USB-Driver\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\USB\USBD\SimulateCDC\User\UART" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

