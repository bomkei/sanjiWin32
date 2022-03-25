
TARGET	= sanji.exe

TOPDIR	?= $(CURDIR)
INCLUDE	= include
SOURCE	= src src/WinLib
BUILD	= build
TEST	= test

DEFINES	= UNICODE

COMMON_FLAGS	:= -g -O2
SFLAGS			:= $(COMMON_FLAGS)
CFLAGS			:= $(SFLAGS) $(INCLUDES) $(foreach def,$(DEFINES),-D $(def))
CXXFLAGS		:= $(CFLAGS) -std=c++20 -Wno-switch
LDFLAGS			:= -Wl,--gc-sections -mwindows

%.o: %.s
	@echo $(notdir $<)
	@gcc -MMD -MP -MF $*.d $(SFLAGS) -c -o $@ $<

%.o: %.c
	@echo $(notdir $<)
	@gcc -MMD -MP -MF $*.d $(CFLAGS) -c -o $@ $<

%.o: %.cc
	@echo $(notdir $<)
	@g++ -MMD -MP -MF $*.d $(CXXFLAGS) -c -o $@ $<

ifneq ($(notdir $(CURDIR)),$(BUILD))

export OUTPUT	= $(CURDIR)/$(TARGET)
export TOPDIR	= $(CURDIR)
export VPATH	= $(foreach dir,$(SOURCE),$(CURDIR)/$(dir))
export INCLUDES	= $(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir))

SFILES		= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.s)))
CFILES		= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES	= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cc)))

export OFILES	= \
	$(SFILES:.s=.o) \
	$(CFILES:.c=.o) \
	$(CXXFILES:.cc=.o)

.PHONY: $(BUILD)

all: $(BUILD)

debug:
	@rm -drf $(BUILD)
	@rm -f $(TARGET)
	@[ -d $(BUILD) ] || mkdir -p $(BUILD)
	@$(MAKE) COMMON_FLAGS="-g -O0" --no-print-directory -C $(BUILD) -f $(TOPDIR)/Makefile

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(TOPDIR)/Makefile

clean:
	@rm -drf $(BUILD)
	@rm -f $(TARGET)

re: clean all

else

DEPENDS	= $(OFILES:.o=.d)

$(OUTPUT): $(OFILES)
	@echo linking...
	@g++ $(LDFLAGS) -o $@ $^

-include $(DEPENDS)

endif