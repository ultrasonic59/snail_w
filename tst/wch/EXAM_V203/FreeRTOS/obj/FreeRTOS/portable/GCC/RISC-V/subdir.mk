################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/RISC-V/port.c 

S_UPPER_SRCS += \
../FreeRTOS/portable/GCC/RISC-V/portASM.S 

OBJS += \
./FreeRTOS/portable/GCC/RISC-V/port.o \
./FreeRTOS/portable/GCC/RISC-V/portASM.o 

S_UPPER_DEPS += \
./FreeRTOS/portable/GCC/RISC-V/portASM.d 

C_DEPS += \
./FreeRTOS/portable/GCC/RISC-V/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/RISC-V/%.o: ../FreeRTOS/portable/GCC/RISC-V/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
FreeRTOS/portable/GCC/RISC-V/%.o: ../FreeRTOS/portable/GCC/RISC-V/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -x assembler-with-cpp -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\MemMang" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

