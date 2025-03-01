# ================================
# Universal Makefile for C & C++
#   -> Native + WebAssembly
# ================================

# 1) 子目录列表
#    如果需要扫描更多子目录，继续添加即可
SUBDIRS = Bsort coremark Fib_recursion File_IO Hanoi matrix_multiplication Qsort Sieve

# 2) 扫描子目录中的 .c / .cpp 文件
C_FILES   = $(foreach d, $(SUBDIRS), $(wildcard $(d)/*.c))
CPP_FILES = $(foreach d, $(SUBDIRS), $(wildcard $(d)/*.cpp))

# 3) 输出文件夹
BIN_DIR = bin

# 4) 生成目标名
# 对每个 C 文件 foo.c，生成:
#   bin/foo.c_c_native.out & bin/foo.c_c_wasm.wasm
C_OUTS  = $(patsubst %.c,   $(BIN_DIR)/%.c_c_native.out, $(C_FILES))
C_WASMS = $(patsubst %.c,   $(BIN_DIR)/%.c_c_wasm.wasm,  $(C_FILES))

# 对每个 C++ 文件 foo.cpp，生成:
#   bin/foo.cpp_cpp_native.out & bin/foo.cpp_cpp_wasm.wasm
CPP_OUTS  = $(patsubst %.cpp, $(BIN_DIR)/%.cpp_cpp_native.out, $(CPP_FILES))
CPP_WASMS = $(patsubst %.cpp, $(BIN_DIR)/%.cpp_cpp_wasm.wasm,  $(CPP_FILES))

# 汇总所有目标
ALL_TARGETS = $(C_OUTS) $(C_WASMS) $(CPP_OUTS) $(CPP_WASMS)

# 5) 编译器与选项
# 5.1) 本地编译 (Native)
CC_NATIVE  = gcc
CXX_NATIVE = g++

CFLAGS_NATIVE   = -O3 -Wall -Wextra
CXXFLAGS_NATIVE = -O3 -Wall -Wextra

# 5.2) WASI SDK 路径
WASI_SDK_PATH = /home/hylanc/wasi-sdk-25.0-x86_64-linux
CC_WASM  = $(WASI_SDK_PATH)/bin/clang
CXX_WASM = $(WASI_SDK_PATH)/bin/clang++

SYSROOT_WASM = $(WASI_SDK_PATH)/share/wasi-sysroot

# 5.3) WASM 编译选项
CFLAGS_WASM = --target=wasm32-wasi \
              -O3 \
              -D_WASI_EMULATED_PROCESS_CLOCKS \
              -Wno-deprecated-declarations

CXXFLAGS_WASM = --target=wasm32-wasi \
                -O3 \
                -D_WASI_EMULATED_PROCESS_CLOCKS \
                -Wno-deprecated-declarations \
                -fno-exceptions

LDFLAGS_WASM = -lwasi-emulated-process-clocks --sysroot=$(SYSROOT_WASM)

# 6) 默认规则: 一次编译所有
all: $(ALL_TARGETS)

# --- 规则 (A) C -> 本地可执行
$(BIN_DIR)/%.c_c_native.out: %.c
	@mkdir -p $(dir $@)
	$(CC_NATIVE) $(CFLAGS_NATIVE) -o $@ $<

# --- 规则 (B) C -> WASM
$(BIN_DIR)/%.c_c_wasm.wasm: %.c
	@mkdir -p $(dir $@)
	$(CC_WASM) $(CFLAGS_WASM) -o $@ $< $(LDFLAGS_WASM)

# --- 规则 (C) C++ -> 本地可执行
$(BIN_DIR)/%.cpp_cpp_native.out: %.cpp
	@mkdir -p $(dir $@)
	$(CXX_NATIVE) $(CXXFLAGS_NATIVE) -o $@ $<

# --- 规则 (D) C++ -> WASM
$(BIN_DIR)/%.cpp_cpp_wasm.wasm: %.cpp
	@mkdir -p $(dir $@)
	$(CXX_WASM) $(CXXFLAGS_WASM) -o $@ $< $(LDFLAGS_WASM)

# 7) 清理
clean:
	@rm -rf $(BIN_DIR)

.PHONY: all clean
