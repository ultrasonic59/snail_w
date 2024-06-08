################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/Peripheral/src/ch32v30x_adc.c \
../SRC/Peripheral/src/ch32v30x_bkp.c \
../SRC/Peripheral/src/ch32v30x_can.c \
../SRC/Peripheral/src/ch32v30x_crc.c \
../SRC/Peripheral/src/ch32v30x_dac.c \
../SRC/Peripheral/src/ch32v30x_dbgmcu.c \
../SRC/Peripheral/src/ch32v30x_dma.c \
../SRC/Peripheral/src/ch32v30x_dvp.c \
../SRC/Peripheral/src/ch32v30x_eth.c \
../SRC/Peripheral/src/ch32v30x_exti.c \
../SRC/Peripheral/src/ch32v30x_flash.c \
../SRC/Peripheral/src/ch32v30x_fsmc.c \
../SRC/Peripheral/src/ch32v30x_gpio.c \
../SRC/Peripheral/src/ch32v30x_i2c.c \
../SRC/Peripheral/src/ch32v30x_iwdg.c \
../SRC/Peripheral/src/ch32v30x_misc.c \
../SRC/Peripheral/src/ch32v30x_opa.c \
../SRC/Peripheral/src/ch32v30x_pwr.c \
../SRC/Peripheral/src/ch32v30x_rcc.c \
../SRC/Peripheral/src/ch32v30x_rng.c \
../SRC/Peripheral/src/ch32v30x_rtc.c \
../SRC/Peripheral/src/ch32v30x_sdio.c \
../SRC/Peripheral/src/ch32v30x_spi.c \
../SRC/Peripheral/src/ch32v30x_tim.c \
../SRC/Peripheral/src/ch32v30x_usart.c \
../SRC/Peripheral/src/ch32v30x_wwdg.c 

OBJS += \
./SRC/Peripheral/src/ch32v30x_adc.o \
./SRC/Peripheral/src/ch32v30x_bkp.o \
./SRC/Peripheral/src/ch32v30x_can.o \
./SRC/Peripheral/src/ch32v30x_crc.o \
./SRC/Peripheral/src/ch32v30x_dac.o \
./SRC/Peripheral/src/ch32v30x_dbgmcu.o \
./SRC/Peripheral/src/ch32v30x_dma.o \
./SRC/Peripheral/src/ch32v30x_dvp.o \
./SRC/Peripheral/src/ch32v30x_eth.o \
./SRC/Peripheral/src/ch32v30x_exti.o \
./SRC/Peripheral/src/ch32v30x_flash.o \
./SRC/Peripheral/src/ch32v30x_fsmc.o \
./SRC/Peripheral/src/ch32v30x_gpio.o \
./SRC/Peripheral/src/ch32v30x_i2c.o \
./SRC/Peripheral/src/ch32v30x_iwdg.o \
./SRC/Peripheral/src/ch32v30x_misc.o \
./SRC/Peripheral/src/ch32v30x_opa.o \
./SRC/Peripheral/src/ch32v30x_pwr.o \
./SRC/Peripheral/src/ch32v30x_rcc.o \
./SRC/Peripheral/src/ch32v30x_rng.o \
./SRC/Peripheral/src/ch32v30x_rtc.o \
./SRC/Peripheral/src/ch32v30x_sdio.o \
./SRC/Peripheral/src/ch32v30x_spi.o \
./SRC/Peripheral/src/ch32v30x_tim.o \
./SRC/Peripheral/src/ch32v30x_usart.o \
./SRC/Peripheral/src/ch32v30x_wwdg.o 

C_DEPS += \
./SRC/Peripheral/src/ch32v30x_adc.d \
./SRC/Peripheral/src/ch32v30x_bkp.d \
./SRC/Peripheral/src/ch32v30x_can.d \
./SRC/Peripheral/src/ch32v30x_crc.d \
./SRC/Peripheral/src/ch32v30x_dac.d \
./SRC/Peripheral/src/ch32v30x_dbgmcu.d \
./SRC/Peripheral/src/ch32v30x_dma.d \
./SRC/Peripheral/src/ch32v30x_dvp.d \
./SRC/Peripheral/src/ch32v30x_eth.d \
./SRC/Peripheral/src/ch32v30x_exti.d \
./SRC/Peripheral/src/ch32v30x_flash.d \
./SRC/Peripheral/src/ch32v30x_fsmc.d \
./SRC/Peripheral/src/ch32v30x_gpio.d \
./SRC/Peripheral/src/ch32v30x_i2c.d \
./SRC/Peripheral/src/ch32v30x_iwdg.d \
./SRC/Peripheral/src/ch32v30x_misc.d \
./SRC/Peripheral/src/ch32v30x_opa.d \
./SRC/Peripheral/src/ch32v30x_pwr.d \
./SRC/Peripheral/src/ch32v30x_rcc.d \
./SRC/Peripheral/src/ch32v30x_rng.d \
./SRC/Peripheral/src/ch32v30x_rtc.d \
./SRC/Peripheral/src/ch32v30x_sdio.d \
./SRC/Peripheral/src/ch32v30x_spi.d \
./SRC/Peripheral/src/ch32v30x_tim.d \
./SRC/Peripheral/src/ch32v30x_usart.d \
./SRC/Peripheral/src/ch32v30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/Peripheral/src/%.o: ../SRC/Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\proj\velograph\snail_w\common\can" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Core" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Peripheral\inc" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\SRC\Debug" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\brd" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\USB_Device" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\include" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\Common" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\FreeRTOS\portable\MemMang" -I"D:\proj\velograph\snail_w\cam_can\wch\cam_can\User\can" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

