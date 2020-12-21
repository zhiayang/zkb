# makefile

AS                  := arm-none-eabi-as
LD                  := arm-none-eabi-ld
CC                  := arm-none-eabi-gcc
CXX                 := arm-none-eabi-g++
SIZE                := arm-none-eabi-size
OBJCOPY             := arm-none-eabi-objcopy
NRF_UTIL            := adafruit-nrfutil

DEVICE_PATH         := /dev/cu.usbmodem14201

OUTPUT_FOLDER       := build
OUTPUT_HEX          := $(OUTPUT_FOLDER)/zkb.hex
OUTPUT_ZIP          := $(OUTPUT_HEX:.hex=.zip)

SDK_PATH            := sdk/nrf-sdk-17.0.2
NRFX_PATH           := $(SDK_PATH)/modules/nrfx
MDK_PATH            := $(NRFX_PATH)/mdk
SOFTDEVICE          := s140
SOFTDEVICE_VER      := 7.2.0
SOFTDEVICE_PATH     := $(SDK_PATH)/components/softdevice/$(SOFTDEVICE)
SOFTDEVICE_INCLUDES := $(SOFTDEVICE_PATH)/headers/ $(SOFTDEVICE_PATH)/headers/nrf52
SOFTDEVICE_FILE     := $(SOFTDEVICE_PATH)/hex/$(SOFTDEVICE)_nrf52_$(SOFTDEVICE_VER)_softdevice.hex

KERNEL_SOURCES      := $(shell find kernel/source -iname "*.c" -or -iname "*.cpp")

SDK_HDR_LIBRARIES   := util delay log strerror timer log/src

SDK_LIBRARIES       := memobj balloc strerror atomic delay sortlist atomic_fifo       \
					   experimental_section_vars ringbuf

SDK_COMPONENTS      := boards toolchain/cmsis/include ../external/fprintf
SDK_INDV_LIB_SRCS   := util/nrf_assert.c util/app_error.c util/app_error_handler_gcc.c      \
					   util/app_error_weak.c timer/app_timer2.c util/app_util_platform.c    \
					   hardfault/hardfault_implementation.c atomic_flags/nrf_atflags.c      \


# stuff that is always used:
MDK_SOURCES_        := gcc_startup_nrf52840.S system_nrf52840.c
MDK_SOURCES         := $(addprefix $(MDK_PATH)/,$(MDK_SOURCES_))

# assume all librariy code is either assembly or C (no c++) -- which is true.
SDK_SOURCES         :=
SDK_SOURCES         += $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_INDV_LIB_SRCS))
ifneq ($(SDK_COMPONENTS),)
	SDK_SOURCES     += $(shell find $(addprefix $(SDK_PATH)/components/,$(SDK_COMPONENTS)) -iname "*.c" -or -iname "*.S" -or -iname "*.s")
endif
ifneq ($(SDK_LIBRARIES),)
	SDK_SOURCES     += $(shell find $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_LIBRARIES)) -iname "*.c" -or -iname "*.S" -or -iname "*.s")
endif

# exclude IAR and Keil stuff
SDK_SOURCES         := $(filter-out %keil.c %iar.c %freertos.c,$(SDK_SOURCES))

SDK_INCLUDES        += $(addprefix $(SDK_PATH)/components/,$(SDK_COMPONENTS))
SDK_INCLUDES        += $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_LIBRARIES))
SDK_INCLUDES        += $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_HDR_LIBRARIES))
SDK_INCLUDES        += $(SDK_PATH)/config/nrf52840/config

MDK_INCLUDES        := $(MDK_PATH) $(NRFX_PATH) $(NRFX_PATH)/hal/ $(NRFX_PATH)/templates/ $(NRFX_PATH)/templates/nRF52840/
KERNEL_INCLUDES     := kernel/include

ALL_INCLUDES        := $(addprefix -I,$(KERNEL_INCLUDES) $(SDK_INCLUDES) $(MDK_INCLUDES) $(SOFTDEVICE_INCLUDES))
ALL_SOURCES         := $(KERNEL_SOURCES) $(SDK_SOURCES) $(MDK_SOURCES)
ALL_OBJECTS         := $(addsuffix .o,$(ALL_SOURCES))


PLATFORM_DEFINES    := -DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DBOARD_PCA10056 \
					   -DCONFIG_GPIO_AS_PINRESET -DFLOAT_ABI_HARD -DNRF52840_XXAA  \
					   -DNRF_SD_BLE_API_VERSION=7 -DS140 -DSOFTDEVICE_PRESENT

PLATFORM_FLAGS      := -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16

WARNINGS            := -Wall -Wextra -Wno-unused-parameter -Wno-expansion-to-defined
COMMON_FLAGS        := -ffunction-sections -fdata-sections -fno-builtin -fshort-enums -fno-strict-aliasing $(WARNINGS)

AS_FLAGS            := -g3 $(PLATFORM_FLAGS) $(PLATFORM_DEFINES)
CC_FLAGS            := -std=gnu11 $(COMMON_FLAGS) $(PLATFORM_FLAGS) $(PLATFORM_DEFINES)
CXX_FLAGS           := -std=c++17 $(COMMON_FLAGS) $(PLATFORM_FLAGS) $(PLATFORM_DEFINES)

LINKER_SCRIPT       := kernel/link.ld
LD_FLAGS            := $(PLATFORM_FLAGS) -L$(MDK_PATH) -T$(LINKER_SCRIPT) -Wl,--gc-sections --specs=nano.specs

LIBS                := -lc -lnosys -lm

.PHONY: flash clean build_kernel
.DEFAULT_GOAL = all

all: $(OUTPUT_ZIP)

$(OUTPUT_ZIP): $(OUTPUT_HEX)
	@$(NRF_UTIL) --verbose dfu genpkg --dev-type 0x0052 --sd-req 0xFFFE --application $(OUTPUT_HEX) $(OUTPUT_ZIP)

$(OUTPUT_HEX): $(ALL_OBJECTS)
	@echo "  $(notdir $@)"
	@$(CC) $(LD_FLAGS) -Wl,-Map=$(@:.hex=.map) -o $@.out $^ $(LIBS)
	@$(OBJCOPY) -O ihex $@.out $@
	@$(SIZE) $@
	@rm -f $@.out

%.cpp.o: %.cpp Makefile
	@echo "  $(notdir $<)"
	@$(CXX) -c -o $@ $(CXX_FLAGS) -Isdk/overrides $(ALL_INCLUDES) $<

%.c.o: %.c Makefile
	@echo "  $(notdir $<)"
	@$(CC) -c -o $@ $(CC_FLAGS) -Isdk/overrides $(ALL_INCLUDES) $<

# god damn...
%.S.o: %.S Makefile
	@echo "  $(notdir $<)"
	@$(CC) -x assembler-with-cpp -c -o $@ $(AS_FLAGS) $<

%.s.o: %.s Makefile
	@echo "  $(notdir $<)"
	@$(CC) -x assembler-with-cpp -c -o $@ $(AS_FLAGS) $<

flash: $(OUTPUT_ZIP)
	@$(NRF_UTIL) --verbose dfu serial -t 1200 --package $(OUTPUT_ZIP) -p $(DEVICE_PATH) -b 115200 --singlebank

clean:
	@find sdk -iname "*.o" | xargs rm
	@find kernel -iname "*.o" | xargs rm
	@rm -f build/*.hex
	@rm -f build/*.zip
	@rm -f build/*.map
	@rm -f build/*.out
