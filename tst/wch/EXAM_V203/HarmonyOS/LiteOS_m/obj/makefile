################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include LiteOS/utils/subdir.mk
-include LiteOS/third_party/bounds_checking_function/src/subdir.mk
-include LiteOS/kernel/src/mm/subdir.mk
-include LiteOS/kernel/src/subdir.mk
-include LiteOS/kernel/arch/risc-v/V4A/gcc/subdir.mk
-include LiteOS/components/power/subdir.mk
-include LiteOS/components/cpup/subdir.mk
-include LiteOS/components/backtrace/subdir.mk
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
LiteOS_m.hex \

SECONDARY_LIST += \
LiteOS_m.lst \

SECONDARY_SIZE += \
LiteOS_m.siz \


# All Target
all: LiteOS_m.elf secondary-outputs

# Tool invocations
LiteOS_m.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "D:\proj\velograph\snail_w\wch\EXAM_V203\HarmonyOS\LiteOS_m\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"LiteOS_m.map" --specs=nano.specs --specs=nosys.specs -o "LiteOS_m.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
LiteOS_m.hex: LiteOS_m.elf
	@	riscv-none-embed-objcopy -O ihex "LiteOS_m.elf"  "LiteOS_m.hex"
	@	@
LiteOS_m.lst: LiteOS_m.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "LiteOS_m.elf" > "LiteOS_m.lst"
	@	@
LiteOS_m.siz: LiteOS_m.elf
	@	riscv-none-embed-size --format=berkeley "LiteOS_m.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) LiteOS_m.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
