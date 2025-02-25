# Makefile for compiling matrix_mul.c to both Native Linux and WebAssembly (WASM) using Wasm3

# ===============================
# Variables
# ===============================

# Compiler for Native
CC_NATIVE = gcc

# Compiler for WASM (WASI SDK's Clang)
WASI_SDK_PATH = /home/hylanc/wasi-sdk-25.0-x86_64-linux
CC_WASM = $(WASI_SDK_PATH)/bin/clang

# Sysroot for WASM
SYSROOT_WASM = $(WASI_SDK_PATH)/share/wasi-sysroot

# Source file
SRC = matrix_mul.c

# Native executable name
NATIVE = matrix_mul_native

# WASM module name
WASM = matrix_mul.wasm

# Compiler flags for Native
CFLAGS_NATIVE = -O3 -Wall -Wextra

# Compiler flags for WASM
CFLAGS_WASM = --target=wasm32-wasi \
             --sysroot=$(SYSROOT_WASM) \
             -O3 \
             -D_WASI_EMULATED_PROCESS_CLOCKS \
             -Wno-deprecated-declarations

# Linker flags for WASM
LDFLAGS_WASM = -lwasi-emulated-process-clocks

# ===============================
# Targets
# ===============================

# Default target: build both Native and WASM
all: native wasm

# Target to build Native executable
native: $(SRC)
	$(CC_NATIVE) $(CFLAGS_NATIVE) -o $(NATIVE) $(SRC)

# Target to build WebAssembly module
wasm: $(SRC)
	$(CC_WASM) $(CFLAGS_WASM) -o $(WASM) $(SRC) $(LDFLAGS_WASM)

# Target to clean generated files
clean:
	rm -f $(NATIVE) $(WASM)

# ===============================
# Phony Targets
# ===============================

.PHONY: all native wasm clean
