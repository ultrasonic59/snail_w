################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TencentOS_Tiny/kernel/pm/tos_pm.c \
../TencentOS_Tiny/kernel/pm/tos_tickless.c 

OBJS += \
./TencentOS_Tiny/kernel/pm/tos_pm.o \
./TencentOS_Tiny/kernel/pm/tos_tickless.o 

C_DEPS += \
./TencentOS_Tiny/kernel/pm/tos_pm.d \
./TencentOS_Tiny/kernel/pm/tos_tickless.d 


# Each subdirectory must supply rules for building sources it contributes
TencentOS_Tiny/kernel/pm/%.o: ../TencentOS_Tiny/kernel/pm/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\rv32\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\TOS_CONFIG" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

