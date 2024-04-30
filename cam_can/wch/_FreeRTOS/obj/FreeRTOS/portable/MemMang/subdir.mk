################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o: ../FreeRTOS/portable/MemMang/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\User" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\FreeRTOS\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

