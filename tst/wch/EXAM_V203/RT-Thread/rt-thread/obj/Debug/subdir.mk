################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/proj/velograph/snail_w/wch/EXAM_V203/SRC/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: D:/proj/velograph/snail_w/wch/EXAM_V203/SRC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\drivers" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include\libc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\misc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\serial" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

