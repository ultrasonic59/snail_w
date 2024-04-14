################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_ch32v20x_D6.S 

OBJS += \
./Startup/startup_ch32v20x_D6.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v20x_D6.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -DCH32V20x_D8W -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\Startup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\drivers" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\include\libc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\libcpu\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\src" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\misc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\drivers\serial" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread\components\finsh" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\RT-Thread\rt-thread\rtthread" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

