################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
EXECUTABLES += \
STM32f103c8t-TestCodes.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32f103c8t-TestCodes.list \

OBJCOPY_HEX += \
STM32f103c8t-TestCodes.hex \

OBJCOPY_BIN += \
STM32f103c8t-TestCodes.bin \


# All Target
all: STM32f103c8t-TestCodes.elf secondary-outputs

# Tool invocations
STM32f103c8t-TestCodes.elf: $(OBJS) $(USER_OBJS) D:\1.Mohamed\Embedded\ITI-ARM-COURSE\STM32f103c8t-TestCodes\STM32F103CBTX_FLASH.ld
	arm-none-eabi-gcc -o "STM32f103c8t-TestCodes.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\1.Mohamed\Embedded\ITI-ARM-COURSE\STM32f103c8t-TestCodes\STM32F103CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32f103c8t-TestCodes.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32f103c8t-TestCodes.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32f103c8t-TestCodes.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32f103c8t-TestCodes.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "STM32f103c8t-TestCodes.hex"
	@echo 'Finished building: $@'
	@echo ' '

STM32f103c8t-TestCodes.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32f103c8t-TestCodes.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
