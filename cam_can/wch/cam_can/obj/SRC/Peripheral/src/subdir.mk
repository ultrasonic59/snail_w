################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Peripheral/src/ch32v30x_adc.c \
../src/Peripheral/src/ch32v30x_bkp.c \
../src/Peripheral/src/ch32v30x_can.c \
../src/Peripheral/src/ch32v30x_crc.c \
../src/Peripheral/src/ch32v30x_dac.c \
../src/Peripheral/src/ch32v30x_dbgmcu.c \
../src/Peripheral/src/ch32v30x_dma.c \
../src/Peripheral/src/ch32v30x_dvp.c \
../src/Peripheral/src/ch32v30x_eth.c \
../src/Peripheral/src/ch32v30x_exti.c \
../src/Peripheral/src/ch32v30x_flash.c \
../src/Peripheral/src/ch32v30x_fsmc.c \
../src/Peripheral/src/ch32v30x_gpio.c \
../src/Peripheral/src/ch32v30x_i2c.c \
../src/Peripheral/src/ch32v30x_iwdg.c \
../src/Peripheral/src/ch32v30x_misc.c \
../src/Peripheral/src/ch32v30x_opa.c \
../src/Peripheral/src/ch32v30x_pwr.c \
../src/Peripheral/src/ch32v30x_rcc.c \
../src/Peripheral/src/ch32v30x_rng.c \
../src/Peripheral/src/ch32v30x_rtc.c \
../src/Peripheral/src/ch32v30x_sdio.c \
../src/Peripheral/src/ch32v30x_spi.c \
../src/Peripheral/src/ch32v30x_tim.c \
../src/Peripheral/src/ch32v30x_usart.c \
../src/Peripheral/src/ch32v30x_wwdg.c 

OBJS += \
./src/Peripheral/src/ch32v30x_adc.o \
./src/Peripheral/src/ch32v30x_bkp.o \
./src/Peripheral/src/ch32v30x_can.o \
./src/Peripheral/src/ch32v30x_crc.o \
./src/Peripheral/src/ch32v30x_dac.o \
./src/Peripheral/src/ch32v30x_dbgmcu.o \
./src/Peripheral/src/ch32v30x_dma.o \
./src/Peripheral/src/ch32v30x_dvp.o \
./src/Peripheral/src/ch32v30x_eth.o \
./src/Peripheral/src/ch32v30x_exti.o \
./src/Peripheral/src/ch32v30x_flash.o \
./src/Peripheral/src/ch32v30x_fsmc.o \
./src/Peripheral/src/ch32v30x_gpio.o \
./src/Peripheral/src/ch32v30x_i2c.o \
./src/Peripheral/src/ch32v30x_iwdg.o \
./src/Peripheral/src/ch32v30x_misc.o \
./src/Peripheral/src/ch32v30x_opa.o \
./src/Peripheral/src/ch32v30x_pwr.o \
./src/Peripheral/src/ch32v30x_rcc.o \
./src/Peripheral/src/ch32v30x_rng.o \
./src/Peripheral/src/ch32v30x_rtc.o \
./src/Peripheral/src/ch32v30x_sdio.o \
./src/Peripheral/src/ch32v30x_spi.o \
./src/Peripheral/src/ch32v30x_tim.o \
./src/Peripheral/src/ch32v30x_usart.o \
./src/Peripheral/src/ch32v30x_wwdg.o 

C_DEPS += \
./src/Peripheral/src/ch32v30x_adc.d \
./src/Peripheral/src/ch32v30x_bkp.d \
./src/Peripheral/src/ch32v30x_can.d \
./src/Peripheral/src/ch32v30x_crc.d \
./src/Peripheral/src/ch32v30x_dac.d \
./src/Peripheral/src/ch32v30x_dbgmcu.d \
./src/Peripheral/src/ch32v30x_dma.d \
./src/Peripheral/src/ch32v30x_dvp.d \
./src/Peripheral/src/ch32v30x_eth.d \
./src/Peripheral/src/ch32v30x_exti.d \
./src/Peripheral/src/ch32v30x_flash.d \
./src/Peripheral/src/ch32v30x_fsmc.d \
./src/Peripheral/src/ch32v30x_gpio.d \
./src/Peripheral/src/ch32v30x_i2c.d \
./src/Peripheral/src/ch32v30x_iwdg.d \
./src/Peripheral/src/ch32v30x_misc.d \
./src/Peripheral/src/ch32v30x_opa.d \
./src/Peripheral/src/ch32v30x_pwr.d \
./src/Peripheral/src/ch32v30x_rcc.d \
./src/Peripheral/src/ch32v30x_rng.d \
./src/Peripheral/src/ch32v30x_rtc.d \
./src/Peripheral/src/ch32v30x_sdio.d \
./src/Peripheral/src/ch32v30x_spi.d \
./src/Peripheral/src/ch32v30x_tim.d \
./src/Peripheral/src/ch32v30x_usart.d \
./src/Peripheral/src/ch32v30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
src/Peripheral/src/%.o: ../src/Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\src\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\UART" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\src\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\src\Peripheral\inc" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

