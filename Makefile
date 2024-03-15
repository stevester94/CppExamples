TOOLBOX_PATH := $(shell realpath _toolbox)
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I$(TOOLBOX_PATH)

# Recursively find all directories containing source files
IGNORE_PATTERN := \.git|vscode|_toolbox|ccls-cache|STL|md5
EXAMPLE_DIRS := $(shell find . -type d -links 2 | grep -vE '$(IGNORE_PATTERN)')

# Get list of source files
EXAMPLE_SRCS := $(foreach dir,$(EXAMPLE_DIRS),$(wildcard $(dir)/*.cpp))

# Generate list of target names (the executables)
EXAMPLE_EXES := $(patsubst %.cpp, %, $(EXAMPLE_SRCS))

all: $(EXAMPLE_EXES)

$(EXAMPLE_EXES): % : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: run run-% all

# Could not get this filter thing working, but it'd be the right way to do this
# run-%: $(filter %, $(EXAMPLE_EXES))
run-%: all
# @echo $@
# @echo $<
# @echo $^
	@echo $* # This matches the '%' apparently
	@./$(shell find . -type f | grep $*$)

clean:
	rm -f $(EXAMPLE_EXES)