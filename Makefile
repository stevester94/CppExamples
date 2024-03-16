TOOLBOX_PATH := $(shell realpath _toolbox)
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I$(TOOLBOX_PATH)

# Recursively find all directories containing source files
IGNORE_PATTERN := \.git|vscode|_toolbox|ccls-cache|STL|md5|json

EXAMPLE_DIRS := $(shell find . -type d -links 2 | grep -vE '$(IGNORE_PATTERN)')
EXAMPLE_EXES := $(foreach dir, $(EXAMPLE_DIRS), $(dir)/out)

.PHONY: all


all: $(EXAMPLE_EXES)

%/out: %/*.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	for dir in $(EXAMPLE_DIRS); do rm $$dir/out; done