################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtthread/components/finsh/cmd.c \
../rtthread/components/finsh/msh.c \
../rtthread/components/finsh/msh_cmd.c \
../rtthread/components/finsh/msh_file.c \
../rtthread/components/finsh/shell.c \
../rtthread/components/finsh/symbol.c 

OBJS += \
./rtthread/components/finsh/cmd.o \
./rtthread/components/finsh/msh.o \
./rtthread/components/finsh/msh_cmd.o \
./rtthread/components/finsh/msh_file.o \
./rtthread/components/finsh/shell.o \
./rtthread/components/finsh/symbol.o 

C_DEPS += \
./rtthread/components/finsh/cmd.d \
./rtthread/components/finsh/msh.d \
./rtthread/components/finsh/msh_cmd.d \
./rtthread/components/finsh/msh_file.d \
./rtthread/components/finsh/shell.d \
./rtthread/components/finsh/symbol.d 


# Each subdirectory must supply rules for building sources it contributes
rtthread/components/finsh/%.o: ../rtthread/components/finsh/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\drivers" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include\libc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\misc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\serial" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

