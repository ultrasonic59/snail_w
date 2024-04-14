################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LiteOS/kernel/src/los_event.c \
../LiteOS/kernel/src/los_init.c \
../LiteOS/kernel/src/los_mux.c \
../LiteOS/kernel/src/los_queue.c \
../LiteOS/kernel/src/los_sched.c \
../LiteOS/kernel/src/los_sem.c \
../LiteOS/kernel/src/los_sortlink.c \
../LiteOS/kernel/src/los_swtmr.c \
../LiteOS/kernel/src/los_task.c \
../LiteOS/kernel/src/los_tick.c 

OBJS += \
./LiteOS/kernel/src/los_event.o \
./LiteOS/kernel/src/los_init.o \
./LiteOS/kernel/src/los_mux.o \
./LiteOS/kernel/src/los_queue.o \
./LiteOS/kernel/src/los_sched.o \
./LiteOS/kernel/src/los_sem.o \
./LiteOS/kernel/src/los_sortlink.o \
./LiteOS/kernel/src/los_swtmr.o \
./LiteOS/kernel/src/los_task.o \
./LiteOS/kernel/src/los_tick.o 

C_DEPS += \
./LiteOS/kernel/src/los_event.d \
./LiteOS/kernel/src/los_init.d \
./LiteOS/kernel/src/los_mux.d \
./LiteOS/kernel/src/los_queue.d \
./LiteOS/kernel/src/los_sched.d \
./LiteOS/kernel/src/los_sem.d \
./LiteOS/kernel/src/los_sortlink.d \
./LiteOS/kernel/src/los_swtmr.d \
./LiteOS/kernel/src/los_task.d \
./LiteOS/kernel/src/los_tick.d 


# Each subdirectory must supply rules for building sources it contributes
LiteOS/kernel/src/%.o: ../LiteOS/kernel/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\backtrace" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\cpup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\power" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\risc-v\V4A\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src\mm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils\internal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

