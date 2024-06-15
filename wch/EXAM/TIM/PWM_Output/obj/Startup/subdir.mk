################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
D:/proj/velograph/snail_w/wch/EXAM/SRC/Startup/startup_ch32v30x_D8.S 

OBJS += \
./Startup/startup_ch32v30x_D8.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v30x_D8.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v30x_D8.o: D:/proj/velograph/snail_w/wch/EXAM/SRC/Startup/startup_ch32v30x_D8.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"D:\proj\velograph\snail_w\wch\EXAM\SRC\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

