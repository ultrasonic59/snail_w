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
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/RISC-V/subdir.mk
-include FreeRTOS/subdir.mk
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
FreeRTOS.hex \

SECONDARY_LIST += \
FreeRTOS.lst \

SECONDARY_SIZE += \
FreeRTOS.siz \


# All Target
all: FreeRTOS.elf secondary-outputs

# Tool invocations
FreeRTOS.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -T "D:\proj\velograph\snail_w\wch\EXAM_V203\FreeRTOS\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"FreeRTOS.map" --specs=nano.specs --specs=nosys.specs -o "FreeRTOS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
FreeRTOS.hex: FreeRTOS.elf
	@	riscv-none-embed-objcopy -O ihex "FreeRTOS.elf"  "FreeRTOS.hex"
	@	@
FreeRTOS.lst: FreeRTOS.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "FreeRTOS.elf" > "FreeRTOS.lst"
	@	@
FreeRTOS.siz: FreeRTOS.elf
	@	riscv-none-embed-size --format=berkeley "FreeRTOS.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) FreeRTOS.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
