################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/croutine.d \
./FreeRTOS/event_groups.d \
./FreeRTOS/list.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/%.o: ../FreeRTOS/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\common\can" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\UART" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

