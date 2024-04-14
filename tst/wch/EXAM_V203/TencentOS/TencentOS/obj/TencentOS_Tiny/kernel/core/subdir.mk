################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TencentOS_Tiny/kernel/core/tos_barrier.c \
../TencentOS_Tiny/kernel/core/tos_binary_heap.c \
../TencentOS_Tiny/kernel/core/tos_bitmap.c \
../TencentOS_Tiny/kernel/core/tos_char_fifo.c \
../TencentOS_Tiny/kernel/core/tos_completion.c \
../TencentOS_Tiny/kernel/core/tos_countdownlatch.c \
../TencentOS_Tiny/kernel/core/tos_event.c \
../TencentOS_Tiny/kernel/core/tos_global.c \
../TencentOS_Tiny/kernel/core/tos_mail_queue.c \
../TencentOS_Tiny/kernel/core/tos_message_queue.c \
../TencentOS_Tiny/kernel/core/tos_mmblk.c \
../TencentOS_Tiny/kernel/core/tos_mmheap.c \
../TencentOS_Tiny/kernel/core/tos_mutex.c \
../TencentOS_Tiny/kernel/core/tos_pend.c \
../TencentOS_Tiny/kernel/core/tos_priority_mail_queue.c \
../TencentOS_Tiny/kernel/core/tos_priority_message_queue.c \
../TencentOS_Tiny/kernel/core/tos_priority_queue.c \
../TencentOS_Tiny/kernel/core/tos_ring_queue.c \
../TencentOS_Tiny/kernel/core/tos_robin.c \
../TencentOS_Tiny/kernel/core/tos_rwlock.c \
../TencentOS_Tiny/kernel/core/tos_sched.c \
../TencentOS_Tiny/kernel/core/tos_sem.c \
../TencentOS_Tiny/kernel/core/tos_stopwatch.c \
../TencentOS_Tiny/kernel/core/tos_sys.c \
../TencentOS_Tiny/kernel/core/tos_task.c \
../TencentOS_Tiny/kernel/core/tos_tick.c \
../TencentOS_Tiny/kernel/core/tos_time.c \
../TencentOS_Tiny/kernel/core/tos_timer.c 

OBJS += \
./TencentOS_Tiny/kernel/core/tos_barrier.o \
./TencentOS_Tiny/kernel/core/tos_binary_heap.o \
./TencentOS_Tiny/kernel/core/tos_bitmap.o \
./TencentOS_Tiny/kernel/core/tos_char_fifo.o \
./TencentOS_Tiny/kernel/core/tos_completion.o \
./TencentOS_Tiny/kernel/core/tos_countdownlatch.o \
./TencentOS_Tiny/kernel/core/tos_event.o \
./TencentOS_Tiny/kernel/core/tos_global.o \
./TencentOS_Tiny/kernel/core/tos_mail_queue.o \
./TencentOS_Tiny/kernel/core/tos_message_queue.o \
./TencentOS_Tiny/kernel/core/tos_mmblk.o \
./TencentOS_Tiny/kernel/core/tos_mmheap.o \
./TencentOS_Tiny/kernel/core/tos_mutex.o \
./TencentOS_Tiny/kernel/core/tos_pend.o \
./TencentOS_Tiny/kernel/core/tos_priority_mail_queue.o \
./TencentOS_Tiny/kernel/core/tos_priority_message_queue.o \
./TencentOS_Tiny/kernel/core/tos_priority_queue.o \
./TencentOS_Tiny/kernel/core/tos_ring_queue.o \
./TencentOS_Tiny/kernel/core/tos_robin.o \
./TencentOS_Tiny/kernel/core/tos_rwlock.o \
./TencentOS_Tiny/kernel/core/tos_sched.o \
./TencentOS_Tiny/kernel/core/tos_sem.o \
./TencentOS_Tiny/kernel/core/tos_stopwatch.o \
./TencentOS_Tiny/kernel/core/tos_sys.o \
./TencentOS_Tiny/kernel/core/tos_task.o \
./TencentOS_Tiny/kernel/core/tos_tick.o \
./TencentOS_Tiny/kernel/core/tos_time.o \
./TencentOS_Tiny/kernel/core/tos_timer.o 

C_DEPS += \
./TencentOS_Tiny/kernel/core/tos_barrier.d \
./TencentOS_Tiny/kernel/core/tos_binary_heap.d \
./TencentOS_Tiny/kernel/core/tos_bitmap.d \
./TencentOS_Tiny/kernel/core/tos_char_fifo.d \
./TencentOS_Tiny/kernel/core/tos_completion.d \
./TencentOS_Tiny/kernel/core/tos_countdownlatch.d \
./TencentOS_Tiny/kernel/core/tos_event.d \
./TencentOS_Tiny/kernel/core/tos_global.d \
./TencentOS_Tiny/kernel/core/tos_mail_queue.d \
./TencentOS_Tiny/kernel/core/tos_message_queue.d \
./TencentOS_Tiny/kernel/core/tos_mmblk.d \
./TencentOS_Tiny/kernel/core/tos_mmheap.d \
./TencentOS_Tiny/kernel/core/tos_mutex.d \
./TencentOS_Tiny/kernel/core/tos_pend.d \
./TencentOS_Tiny/kernel/core/tos_priority_mail_queue.d \
./TencentOS_Tiny/kernel/core/tos_priority_message_queue.d \
./TencentOS_Tiny/kernel/core/tos_priority_queue.d \
./TencentOS_Tiny/kernel/core/tos_ring_queue.d \
./TencentOS_Tiny/kernel/core/tos_robin.d \
./TencentOS_Tiny/kernel/core/tos_rwlock.d \
./TencentOS_Tiny/kernel/core/tos_sched.d \
./TencentOS_Tiny/kernel/core/tos_sem.d \
./TencentOS_Tiny/kernel/core/tos_stopwatch.d \
./TencentOS_Tiny/kernel/core/tos_sys.d \
./TencentOS_Tiny/kernel/core/tos_task.d \
./TencentOS_Tiny/kernel/core/tos_tick.d \
./TencentOS_Tiny/kernel/core/tos_time.d \
./TencentOS_Tiny/kernel/core/tos_timer.d 


# Each subdirectory must supply rules for building sources it contributes
TencentOS_Tiny/kernel/core/%.o: ../TencentOS_Tiny/kernel/core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\rv32\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\TOS_CONFIG" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

