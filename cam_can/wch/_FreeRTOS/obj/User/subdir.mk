################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\User" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

