################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/USB_Device/ch32v30x_usbhs_device.c \
../User/USB_Device/usb_desc.c 

OBJS += \
./User/USB_Device/ch32v30x_usbhs_device.o \
./User/USB_Device/usb_desc.o 

C_DEPS += \
./User/USB_Device/ch32v30x_usbhs_device.d \
./User/USB_Device/usb_desc.d 


# Each subdirectory must supply rules for building sources it contributes
User/USB_Device/%.o: ../User/USB_Device/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\SimulateCDC-HID_hs\User\UART" -I"D:\proj\velograph\snail_w\wch\SimulateCDC-HID_hs\User\USB_Device" -I"D:\proj\velograph\snail_w\wch\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\SRC\Core" -I"D:\proj\velograph\snail_w\wch\SimulateCDC-HID_hs\User" -I"D:\proj\velograph\snail_w\wch\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

