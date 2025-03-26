################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include app/subdir.mk
-include Old_and_NewAbstraction/New/Hardware_Abstraction/STM32/STM32F0/subdir.mk
-include Old_and_NewAbstraction/New/Hardware_Abstraction/Includes/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include CANopenNodeInterface/subdir.mk
-include CANopenNode/storage/subdir.mk
-include CANopenNode/extra/subdir.mk
-include CANopenNode/309/subdir.mk
-include CANopenNode/305/subdir.mk
-include CANopenNode/304/subdir.mk
-include CANopenNode/303/subdir.mk
-include CANopenNode/301/subdir.mk
-include CANopenNode/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := NucleoF072RB_CANSlave
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NucleoF072RB_CANSlave.elf \

MAP_FILES += \
NucleoF072RB_CANSlave.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NucleoF072RB_CANSlave.list \


# All Target
all: main-build

# Main-build Target
main-build: NucleoF072RB_CANSlave.elf secondary-outputs

# Tool invocations
NucleoF072RB_CANSlave.elf NucleoF072RB_CANSlave.map: $(OBJS) $(USER_OBJS) C:\Users\ketan.singh\Desktop\Microcontroller-Nucleo-G071RB\Tests_tobedeleted\NucleoF072RB_CANSlave\NucleoF072RB_CANSlave\STM32F072RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "NucleoF072RB_CANSlave.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\ketan.singh\Desktop\Microcontroller-Nucleo-G071RB\Tests_tobedeleted\NucleoF072RB_CANSlave\NucleoF072RB_CANSlave\STM32F072RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NucleoF072RB_CANSlave.map" -Wl,--gc-sections -static -L"C:\ST\STM32CubeIDE_1.17.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.win32_1.1.0.202410251130\tools\arm-none-eabi\include\c++\12.3.1" --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NucleoF072RB_CANSlave.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NucleoF072RB_CANSlave.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) NucleoF072RB_CANSlave.elf NucleoF072RB_CANSlave.list NucleoF072RB_CANSlave.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
