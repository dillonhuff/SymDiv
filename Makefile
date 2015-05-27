# Project path settings
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build

# Clang / LLVM settings
LLVM_SRC_PATH :=/Users/dillon/cppWorkspace/llvm

LLVM_BUILD_PATH := /Users/dillon/cppWorkspace/build-llvm
LLVM_BIN_PATH := $(LLVM_BUILD_PATH)/bin

LLVM_CXXFLAGS := `$(LLVM_BIN_PATH)/llvm-config --cxxflags`
LLVM_LDFLAGS := `$(LLVM_BIN_PATH)/llvm-config --ldflags --libs --system-libs`

LLVM_LDFLAGS_NOLIBS := `$(LLVM_BIN_PATH)/llvm-config --ldflags`
PLUGIN_LDFLAGS := -shared

CLANG_INCLUDES := \
	-I$(LLVM_SRC_PATH)/tools/clang/include \
	-I$(LLVM_BUILD_PATH)/tools/clang/include

CLANG_LIBS := \
	-Wl, \
	-lclangAST \
	-lclangAnalysis \
	-lclangBasic \
	-lclangCodeGen \
	-lclangDriver \
	-lclangEdit \
	-lclangFrontend \
	-lclangFrontendTool \
	-lclangLex \
	-lclangParse \
	-lclangSema \
	-lclangEdit \
	-lclangASTMatchers \
	-lclangRewrite \
	-lclangRewriteFrontend \
	-lclangStaticAnalyzerFrontend \
	-lclangStaticAnalyzerCheckers \
	-lclangStaticAnalyzerCore \
	-lclangSerialization \
	-lclangToolingCore \
	-lclangTooling \
	-Wl,

# Z3 settings
Z3_PATH := /Users/dillon/cppWorkspace/z3
Z3_API_PATH := $(Z3_PATH)/src/api
Z3_CPP_API_PATH := $(Z3_API_PATH)/c++
Z3_LIB_PATH := /Library/lib/libz3.dylib
Z3_FLAGS := -I$(Z3_API_PATH) -I$(Z3_CPP_API_PATH) 

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -fno-rtti -O2 -g -I./$(SRC_DIR) -I./$(TEST_DIR)
PLUGIN_CXXFLAGS := -fpic

# Symbolic executor tests
SYM_EXE_SRC_DIR := $(SRC_DIR)/SymbolicExecution
SYM_EXE_TEST_DIR := $(TEST_DIR)/SymbolicExecution

SYM_EXE_SRCS := $(shell find $(SYM_EXE_SRC_DIR) -type f -name '*.cpp')
SYM_EXE_TEST_SRCS := $(shell find $(SYM_EXE_TEST_DIR) -type f -name '*.cpp')

SYM_EXE_OBJS := $(patsubst %.cpp, %.o, $(SYM_EXE_SRCS))

SYM_EXE_TEST_OBJS := $(patsubst %.cpp, %.o, $(SYM_EXE_TEST_SRCS))
SYM_EXE_TEST_OBJS += $(SYM_EXE_OBJS)

# Clang interface
CLANG_INTERFACE_SRC_DIR = $(SRC_DIR)/ClangInterface
CLANG_INTERFACE_SRCS := $(shell find $(CLANG_INTERFACE_SRC_DIR) -type f -name '*.cpp')
CLANG_INTERFACE_OBJS := $(patsubst %.cpp, %.o, $(CLANG_INTERFACE_SRCS))

# Header files
ALL_HEADERS := $(shell find $(SRC_DIR) -type f -name '*.h')
ALL_HEADERS += $(shell find $(TEST_DIR) -type f -name '*.h')

# Build rules
.PHONY: all
all: set_z3_path \
	make_builddir \
	$(BUILD_DIR)/sym_exe_tests \
	$(BUILD_DIR)/clang_interface

tests: $(BUILD_DIR)/sym_exe_tests

set_z3_path:
	@export DYLD_LIBRARY_PATH="/Library/lib/"

.PHONY: make_builddir
make_builddir:
	@test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

$(SYM_EXE_SRC_DIR)/%.o: $(SYM_EXE_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(Z3_FLAGS) $^ -c -o $@

$(SYM_EXE_TEST_DIR)/%.o: $(SYM_EXE_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(Z3_FLAGS) $^ -c -o $@

$(CLANG_INTERFACE_SRC_DIR)/%.o: $(CLANG_INTERFACE_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(Z3_FLAGS) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) $^ -c -o $@

$(BUILD_DIR)/clang_interface: $(CLANG_INTERFACE_OBJS) $(SYM_EXE_OBJS)
	$(CXX) $(CXXFLAGS) $(Z3_FLAGS) $(Z3_LIB_PATH) $(LLVM_CXXFLAGS) $(CLANG_INCLUDES) $^ $(CLANG_LIBS) $(LLVM_LDFLAGS) -o $@

$(BUILD_DIR)/sym_exe_tests: $(SYM_EXE_TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(Z3_FLAGS) $(Z3_LIB_PATH) $^ -o $@

.PHONY: clean
clean:
	find . -type f -name '*.o' -delete
	rm -rf $(BUILD_DIR)/*
