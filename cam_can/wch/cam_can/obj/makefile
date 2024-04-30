################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Startup/subdir.mk
-include src/Peripheral/src/subdir.mk
-include src/Debug/subdir.mk
-include src/Core/subdir.mk
-include User/brd/subdir.mk
-include User/USB_Device/subdir.mk
-include User/UART/subdir.mk
-include User/CAN/subdir.mk
-include User/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/RISC-V/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
cam_can.hex \

SECONDARY_LIST += \
cam_can.lst \

SECONDARY_SIZE += \
cam_can.siz \


# All Target
all: cam_can.elf secondary-outputs

# Tool invocations
cam_can.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\proj\velograph\snail_w\cam_can\wch\cam_can\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"cam_can.map" --specs=nano.specs --specs=nosys.specs -o "cam_can.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
cam_can.hex: cam_can.elf
	@	riscv-none-embed-objcopy -O ihex "cam_can.elf"  "cam_can.hex"
	@	@
cam_can.lst: cam_can.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "cam_can.elf" > "cam_can.lst"
	@	@
cam_can.siz: cam_can.elf
	@	riscv-none-embed-size --format=berkeley "cam_can.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) cam_can.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
