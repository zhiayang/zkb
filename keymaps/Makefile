# Makefile

SOURCES         := $(shell find source -iname "*.c" -or -iname "*.cpp")
OBJECTS         := $(addsuffix .o,$(SOURCES))
DEPS            := $(OBJECTS:.o=.d)
INCLUDES        := -Iinclude                            \
				   -I$(PROJECT_ROOT)/kernel/include/    \
				   -I$(PROJECT_ROOT)/hal/include/

.PHONY: all
.DEFAULT_GOAL: all

all: $(OUTPUT_FOLDER)/keymap.a

$(OUTPUT_FOLDER)/keymap.a: $(OBJECTS)
	@$(AR) rcs $@ $^

%.c.o: %.c
	@echo "  keymap: $(notdir $<)"
	@$(CC) -c -o $@ $(CC_FLAGS) $(INCLUDES) -MMD -MP $<

%.cpp.o: %.cpp
	@echo "  keymap: $(notdir $<)"
	@$(CXX) -c -o $@ $(CXX_FLAGS) $(INCLUDES) -MMD -MP $<


-include $(DEPS)
