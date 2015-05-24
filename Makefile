# Project path settings
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -fno-rtti -O2 -g -I./$(SRC_DIR) -I./$(TEST_DIR)
PLUGIN_CXXFLAGS := -fpic

# Symbolic executor tests
SYM_EXE_SRC_DIR := $(SRC_DIR)/SymbolicExecution
SYM_EXE_TEST_DIR := $(TEST_DIR)/SymbolicExecution

SYM_EXE_SRCS := $(shell find $(SYM_EXE_SRC_DIR) -type f -name '*.cpp')
SYM_EXE_SRCS += $(shell find $(SYM_EXE_TEST_DIR) -type f -name '*.cpp')

SYM_EXE_OBJS := $(patsubst %.cpp, %.o, $(SYM_EXE_SRCS))

ALL_HEADERS := $(shell find $(SRC_DIR) -type f -name '*.h')
ALL_HEADERS += $(shell find $(TEST_DIR) -type f -name '*.h')

# Build rules
.PHONY: all
all: make_builddir \
	$(BUILD_DIR)/sym_exe_tests

.PHONY: make_builddir
make_builddir:
	@test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) \
	$(CLANG_LIBS) $(LLVM_LDFLAGS) $^ -c -o $@

$(BUILD_DIR)/sym_exe_tests: $(SYM_EXE_OBJS)
	$(CXX) $(CXXFLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) $^ \
	$(CLANG_LIBS) $(LLVM_LDFLAGS) -o $@

.PHONY: clean
clean:
	find . -type f -name '*.o' -delete
	rm -rf $(BUILD_DIR)/*
