################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/USB_Device/subdir.mk
-include User/UART/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
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
SimulateCDC-HID.hex \

SECONDARY_LIST += \
SimulateCDC-HID.lst \

SECONDARY_SIZE += \
SimulateCDC-HID.siz \


# All Target
all: SimulateCDC-HID.elf secondary-outputs

# Tool invocations
SimulateCDC-HID.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\proj\velograph\snail_w\wch\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SimulateCDC-HID.map" --specs=nano.specs --specs=nosys.specs -o "SimulateCDC-HID.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
SimulateCDC-HID.hex: SimulateCDC-HID.elf
	@	riscv-none-embed-objcopy -O ihex "SimulateCDC-HID.elf"  "SimulateCDC-HID.hex"
	@	@
SimulateCDC-HID.lst: SimulateCDC-HID.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SimulateCDC-HID.elf" > "SimulateCDC-HID.lst"
	@	@
SimulateCDC-HID.siz: SimulateCDC-HID.elf
	@	riscv-none-embed-size --format=berkeley "SimulateCDC-HID.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SimulateCDC-HID.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
