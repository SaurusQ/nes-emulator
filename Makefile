CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -g -Isrc
DEPFLAGS ?= -MMD -MP -MF $(@:.o=.d)
LDFLAGS  ?=
TARGET ?= nes-emulator

BUILDDIR := build
BINDIR   := bin


# Find all .cpp/.c files in repo (exclude build/bin/.git)
SRCS := $(shell find . -type f \( -name '*.cpp' -o -name '*.c' \) \
	-not -path "./$(BUILDDIR)/*" -not -path "./$(BINDIR)/*" -not -path "./.git/*" | sed 's|^\./||')

OBJS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

DEPS := $(OBJS:.o=.d)

.PHONY: all clean run debug

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

run: all
	./$(BINDIR)/$(TARGET)

debug: CXXFLAGS += -g -O0
debug: clean all

clean:
	rm -rf $(BUILDDIR) $(BINDIR)