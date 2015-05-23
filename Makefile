# LLVM path settings
LLVM_SRC_PATH :=/home/dillon/cppWorkspace/llvm
LLVM_BUILD_PATH := /home/dillon/cppWorkspace/build
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin

LLVM_CXXFLAGS := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
LLVM_LDFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --libs --system-libs`

LLVM_LDFLAGS_NOLIBS := `$(LLVM_BIN_PATH)/llvm-config --ldflags`
PLUGIN_LDFLAGS := -shared

CLANG_INCLUDES := \
	-I$(LLVM_SRC_PATH)/tools/clang/include \
	-I$(LLVM_BUILD_PATH)/tools/clang/include

CLANG_LIBS := \
	-Wl,--start-group \
	-lclangAnalysis \
	-lclangBasic \
	-lclangCodeGen \
	-lclangDriver \
	-lclangEdit \
	-lclangFrontend \
	-lclangLex \
	-lclangParse \
	-lclangSema \
	-lclangEdit \
	-lclangASTMatchers \
	-lclangRewrite \
	-lclangRewriteFrontend \
	-Wl,--end-group

# Project path settings
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build

# Compiler settings
CXX := g++
CXXFLAGS := -fno-rtti -O0 -g -I./$(SRC_DIR) -I./$(TEST_DIR)
PLUGIN_CXXFLAGS := -fpic

# Individual project components
SYM_EXE_SRC_DIR := $(SRC_DIR)/SymbolicExecution
SYM_EXE_TEST_DIR := $(TEST_DIR)/SymbolicExecution

SYM_EXE_SRCS := $(shell find $(SYM_EXE_SRC_DIR) -type f -name '*.cpp')
SYM_EXE_SRCS += $(shell find $(SYM_EXE_TEST_DIR) -type f -name '*.cpp')

SYM_EXE_OBJS := $(patsubst %.cpp, %.o, $(SYM_EXE_SRCS))

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
