################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Core/core_riscv.c 

OBJS += \
./src/Core/core_riscv.o 

C_DEPS += \
./src/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
src/Core/%.o: ../src/Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\src\Core" -I"D:\proj\velograph\snail_w\common\can" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\User\UART" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\src\Debug" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\src\Peripheral\inc" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\User" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS\include" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w_\cam_can\wch\cam_can\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

