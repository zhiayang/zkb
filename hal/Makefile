# Makefile

SOFTDEVICE          := s140
SOFTDEVICE_VER      := 7.2.0
SOFTDEVICE_PATH     := $(SDK_PATH)/components/softdevice/$(SOFTDEVICE)
SOFTDEVICE_INCLUDES := $(SOFTDEVICE_PATH)/headers/ $(SOFTDEVICE_PATH)/headers/nrf52
SOFTDEVICE_FILE     := $(SOFTDEVICE_PATH)/hex/$(SOFTDEVICE)_nrf52_$(SOFTDEVICE_VER)_softdevice.hex


SDK_HDR_LIBRARIES   := util delay log strerror timer log/src usbd/class usbd/class/cdc usbd/class/cdc/acm

SDK_HDR_COMPONENTS  := softdevice/common

SDK_LIBRARIES       := memobj balloc strerror atomic delay sortlist atomic_fifo       \
					   experimental_section_vars ringbuf usbd usbd/class/cdc/acm

SDK_COMPONENTS      := boards toolchain/cmsis/include ../external/fprintf ../external/utf_converter

SDK_INDV_LIB_SRCS   := util/nrf_assert.c util/app_error.c util/app_error_handler_gcc.c      \
					   util/app_error_weak.c timer/app_timer2.c util/app_util_platform.c    \
					   hardfault/hardfault_implementation.c atomic_flags/nrf_atflags.c      \
					   log/src/nrf_log_frontend.c

SDK_EXTRA_SRCS      := components/softdevice/common/nrf_sdh.c   \
					   modules/nrfx/mdk/gcc_startup_nrf52840.S  \
					   modules/nrfx/mdk/system_nrf52840.c       \
					   modules/nrfx/soc/nrfx_atomic.c           \
					   modules/nrfx/drivers/src/nrfx_usbd.c     \
					   modules/nrfx/drivers/src/nrfx_clock.c    \
					   modules/nrfx/drivers/src/nrfx_power.c    \
					   integration/nrfx/legacy/nrf_drv_clock.c  \
					   integration/nrfx/legacy/nrf_drv_power.c


# prepend the paths appropriately.
SDK_SOURCES         := $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_INDV_LIB_SRCS))  \
					   $(addprefix $(SDK_PATH)/,$(SDK_EXTRA_SRCS))

ifneq ($(SDK_COMPONENTS),)
	SDK_SOURCES     += $(shell find $(addprefix $(SDK_PATH)/components/,$(SDK_COMPONENTS)) -iname "*.c" -or -iname "*.S" -or -iname "*.s")
endif

ifneq ($(SDK_LIBRARIES),)
	SDK_SOURCES     += $(shell find $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_LIBRARIES)) -iname "*.c" -or -iname "*.S" -or -iname "*.s")
endif

# exclude non arm-gcc stuff
SDK_SOURCES         := $(filter-out %keil.c %iar.c %freertos.c,$(SDK_SOURCES))

SDK_INCLUDES        := $(addprefix $(SDK_PATH)/components/,$(SDK_COMPONENTS))               \
					   $(addprefix $(SDK_PATH)/components/,$(SDK_HDR_COMPONENTS))           \
					   $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_LIBRARIES))      \
					   $(addprefix $(SDK_PATH)/components/libraries/,$(SDK_HDR_LIBRARIES))  \
					   $(SDK_PATH)/modules/nrfx/mdk/                                        \
					   $(SDK_PATH)/modules/nrfx $(SDK_PATH)/modules/nrfx/hal/               \
					   $(SDK_PATH)/modules/nrfx/drivers/include/                            \
					   $(SDK_PATH)/integration/nrfx/legacy/                                 \
					   $(SDK_PATH)/integration/nrfx/


ALL_INCLUDES        := -Iinclude/                       \
					   -I$(PROJECT_ROOT)/sdk/overrides  \
					   $(addprefix -I,$(SDK_INCLUDES))  \
					   $(addprefix -I,$(SOFTDEVICE_INCLUDES))

ALL_SOURCES         := $(shell find source -iname "*.c" -or -iname "*.cpp") $(SDK_SOURCES)
ALL_OBJECTS         := $(addsuffix .o,$(ALL_SOURCES))
ALL_DEPS            := $(ALL_OBJECTS:.o=.d)

.PHONY: all
.DEFAULT_GOAL = all

all: $(OUTPUT_FOLDER)/hal.a

$(OUTPUT_FOLDER)/hal.a: $(ALL_OBJECTS)
	@$(AR) rcs $@ $^

%.c.o: %.c
	@echo "  hal: $(notdir $<)"
	@$(CC) -c -o $@ $(CC_FLAGS) $(ALL_INCLUDES) -MMD -MP $<

%.cpp.o: %.cpp
	@echo "  hal: $(notdir $<)"
	@$(CXX) -c -o $@ $(CXX_FLAGS) $(ALL_INCLUDES) -MMD -MP $<

# god damn...
%.S.o: %.S Makefile
	@echo "  hal: $(notdir $<)"
	@$(CC) -x assembler-with-cpp -c -o $@ $(AS_FLAGS) $<

%.s.o: %.s Makefile
	@echo "  hal: $(notdir $<)"
	@$(CC) -x assembler-with-cpp -c -o $@ $(AS_FLAGS) $<

-include $(ALL_DEPS)
