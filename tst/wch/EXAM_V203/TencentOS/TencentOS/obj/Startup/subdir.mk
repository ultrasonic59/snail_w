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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\Startup" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\common\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\arch\risc-v\rv32\gcc" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\core\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\hal\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\kernel\pm\include" -I"D:\proj\velograph\snail_w\wch\EXAM_V203\TencentOS\TencentOS\TencentOS_Tiny\TOS_CONFIG" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

