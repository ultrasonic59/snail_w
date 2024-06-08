################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/ch32v30x_usbhs_device.c \
../User/main.c \
../User/system_ch32v30x.c \
../User/usb_desc.c \
../User/usbd_compatibility_hid.c 

OBJS += \
./User/ch32v30x_it.o \
./User/ch32v30x_usbhs_device.o \
./User/main.o \
./User/system_ch32v30x.o \
./User/usb_desc.o \
./User/usbd_compatibility_hid.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/ch32v30x_usbhs_device.d \
./User/main.d \
./User/system_ch32v30x.d \
./User/usb_desc.d \
./User/usbd_compatibility_hid.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\SRC\Core" -I"D:\proj\velograph\snail_w\wch\CompatibilityHID_hs1\User" -I"D:\proj\velograph\snail_w\wch\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

