################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LiteOS/kernel/arch/risc-v/V4A/gcc/los_context.c \
../LiteOS/kernel/arch/risc-v/V4A/gcc/los_interrupt.c \
../LiteOS/kernel/arch/risc-v/V4A/gcc/los_timer.c 

S_UPPER_SRCS += \
../LiteOS/kernel/arch/risc-v/V4A/gcc/los_dispatch.S \
../LiteOS/kernel/arch/risc-v/V4A/gcc/los_exc.S 

OBJS += \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_context.o \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_dispatch.o \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_exc.o \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_interrupt.o \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_timer.o 

S_UPPER_DEPS += \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_dispatch.d \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_exc.d 

C_DEPS += \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_context.d \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_interrupt.d \
./LiteOS/kernel/arch/risc-v/V4A/gcc/los_timer.d 


# Each subdirectory must supply rules for building sources it contributes
LiteOS/kernel/arch/risc-v/V4A/gcc/%.o: ../LiteOS/kernel/arch/risc-v/V4A/gcc/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\User" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\backtrace" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\cpup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\power" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\risc-v\V4A\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src\mm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils\internal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\src" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
LiteOS/kernel/arch/risc-v/V4A/gcc/%.o: ../LiteOS/kernel/arch/risc-v/V4A/gcc/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -x assembler-with-cpp -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Startup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\risc-v\V4A\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Debug" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\power" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\cpup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\components\backtrace" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\third_party\bounds_checking_function\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\utils\internal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\arch\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\LiteOS\kernel\src\mm" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

