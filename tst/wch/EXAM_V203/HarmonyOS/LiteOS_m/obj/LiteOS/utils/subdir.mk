################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LiteOS/utils/los_debug.c \
../LiteOS/utils/los_error.c \
../LiteOS/utils/los_hook.c 

OBJS += \
./LiteOS/utils/los_debug.o \
./LiteOS/utils/los_error.o \
./LiteOS/utils/los_hook.o 

C_DEPS += \
./LiteOS/utils/los_debug.d \
./LiteOS/utils/los_error.d \
./LiteOS/utils/los_hook.d 


# Each subdirectory must supply rules for building sources it contributes
LiteOS/utils/%.o: ../LiteOS/utils/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\backtrace" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\cpup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\power" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\risc-v\V4A\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src\mm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils\internal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

