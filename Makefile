# Makefile

AR                  := arm-none-eabi-ar
AS                  := arm-none-eabi-as
LD                  := arm-none-eabi-ld
CC                  := arm-none-eabi-gcc
CXX                 := arm-none-eabi-g++
SIZE                := arm-none-eabi-size
OBJCOPY             := arm-none-eabi-objcopy
NRF_UTIL            := adafruit-nrfutil

DEVICE_PATH         ?= /dev/cu.usbmodem14201

PROJECT_ROOT        := $(shell pwd)
OUTPUT_FOLDER       := $(PROJECT_ROOT)/build
OUTPUT_HEX          := $(OUTPUT_FOLDER)/zkb.hex
OUTPUT_ZIP          := $(OUTPUT_HEX:.hex=.zip)
SDK_PATH            := $(PROJECT_ROOT)/sdk/nrf-sdk-17.0.2

PLATFORM_DEFINES    := -DBOARD_NICE_NANO_NRF52840 -DCUSTOM_BOARD_INC=board_nice_nano            \
                       -DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DBOARD_NICE_NANO_NRF52840    \
                       -DCONFIG_GPIO_AS_PINRESET -DFLOAT_ABI_HARD -DNRF52840_XXAA               \
                       -DNRF_SD_BLE_API_VERSION=7 -DS140 -DSOFTDEVICE_PRESENT

PLATFORM_FLAGS      := -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16

WARNINGS            := -Wall -Wextra -Wno-unused-parameter -Wno-expansion-to-defined
COMMON_FLAGS        := -ffunction-sections -fdata-sections -fno-builtin -fshort-enums -fno-strict-aliasing $(WARNINGS)

AS_FLAGS            := -g3 $(PLATFORM_FLAGS) $(PLATFORM_DEFINES)
CC_FLAGS            := -std=gnu11 $(COMMON_FLAGS) $(PLATFORM_FLAGS) $(PLATFORM_DEFINES) -Werror=implicit-function-declaration
CXX_FLAGS           := -std=c++17 $(COMMON_FLAGS) $(PLATFORM_FLAGS) $(PLATFORM_DEFINES)

LINKER_SCRIPT       := $(PROJECT_ROOT)/sdk/overrides/link.ld
LD_FLAGS            := -flto $(PLATFORM_FLAGS) -L$(SDK_PATH)/modules/nrfx/mdk -T$(LINKER_SCRIPT) -Wl,--gc-sections --specs=nano.specs

LIBS                := -lc -lnosys -lm

HAL_OBJ             := $(OUTPUT_FOLDER)/hal.a
KERNEL_OBJ          := $(OUTPUT_FOLDER)/kernel.a

.PHONY: all flash clean kernel hal
.DEFAULT_GOAL = all

all: $(OUTPUT_ZIP)
hal: $(OUTPUT_FOLDER)/hal.a
kernel: $(OUTPUT_FOLDER)/kernel.a

$(HAL_OBJ): $(shell find hal -type f)
	@$(MAKE) -C hal/

$(KERNEL_OBJ): $(shell find kernel -type f)
	@$(MAKE) -C kernel/

$(OUTPUT_ZIP): $(OUTPUT_HEX)
	@$(NRF_UTIL) --verbose dfu genpkg --dev-type 0x0052 --sd-req 0xFFFE --application $(OUTPUT_HEX) $(OUTPUT_ZIP)

flash: $(OUTPUT_ZIP)
	@$(NRF_UTIL) --verbose dfu serial -t 1200 --package $(OUTPUT_ZIP) -p $(DEVICE_PATH) -b 115200 --singlebank

$(OUTPUT_HEX): $(HAL_OBJ) $(KERNEL_OBJ)
	@mkdir -p build/
	@echo "  output: $(notdir $@)"
	@$(CXX) $(LD_FLAGS) -Wl,-Map=$(@:.hex=.map) -o $@.out -Wl,--start-group $^ -Wl,--end-group $(LIBS)
	@$(OBJCOPY) -O ihex $@.out $@
	@$(SIZE) -G $@.out
	@rm -f $@.out

clean:
	@find sdk -iname "*.o" | xargs rm
	@find hal -iname "*.o" | xargs rm
	@find kernel -iname "*.o" | xargs rm
	@rm -f build/*.a
	@rm -f build/*.hex
	@rm -f build/*.zip
	@rm -f build/*.map
	@rm -f build/*.out

-include $(ALL_DEPS)

# export these to submakes
export AR
export AS
export LD
export CC
export CXX
export SDK_PATH
export PROJECT_ROOT
export OUTPUT_FOLDER

export PLATFORM_DEFINES
export PLATFORM_FLAGS
export COMMON_FLAGS
export WARNINGS
export AS_FLAGS
export CC_FLAGS
export CXX_FLAGS
