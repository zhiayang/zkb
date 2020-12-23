# Makefile

KEYBOARD_FOLDER := $(PROJECT_ROOT)/keyboards/$(KEYBOARD)

SOURCES         := $(shell find source -iname "*.c" -or -iname "*.cpp") \
				   $(shell find $(KEYBOARD_FOLDER)/layout/$(LAYOUT) -iname "*.c" -or -iname "*.cpp")

OBJECTS         := $(addsuffix .o,$(SOURCES))
DEPS            := $(OBJECTS:.o=.d)
INCLUDES        := -Iinclude                                \
				   -I$(PROJECT_ROOT)/hal/include            \
				   -I$(PROJECT_ROOT)/sdk/overrides          \
				   -I$(KEYBOARD_FOLDER)                     \
				   -I$(KEYBOARD_FOLDER)/layouts/$(LAYOUT)

.PHONY: all
.DEFAULT_GOAL: all

all: $(OUTPUT_FOLDER)/kernel.a

$(OUTPUT_FOLDER)/kernel.a: $(OBJECTS)
	@$(AR) rcs $@ $^

%.c.o: %.c
	@echo "  kernel: $(notdir $<)"
	@$(CC) -c -o $@ $(CC_FLAGS) $(INCLUDES) -MMD -MP $<

%.cpp.o: %.cpp
	@echo "  kernel: $(notdir $<)"
	@$(CXX) -c -o $@ $(CXX_FLAGS) $(INCLUDES) -MMD -MP $<


-include $(DEPS)
