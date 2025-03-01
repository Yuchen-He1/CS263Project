# Makefile for compiling Bsort.cpp to both Native Linux and WebAssembly (WASM) using WASI SDK's clang++

# ===============================
# Variables
# ===============================

# Compiler for Native (C++)
CC_NATIVE = g++

# Compiler for WASM (WASI SDK's clang++)
WASI_SDK_PATH = /home/hylanc/wasi-sdk-25.0-x86_64-linux
CC_WASM = $(WASI_SDK_PATH)/bin/clang++

# Sysroot for WASM
SYSROOT_WASM = $(WASI_SDK_PATH)/share/wasi-sysroot

# Source file
SRC = Bsort.cpp

# Output names
NATIVE = Bsort.out
WASM = Bsort.wasm

# Compiler flags for Native
CFLAGS_NATIVE = -O3 -Wall -Wextra

# Compiler flags for WASM
CFLAGS_WASM = --target=wasm32-wasi -O3 -D_WASI_EMULATED_PROCESS_CLOCKS -Wno-deprecated-declarations -fno-exceptions

# Linker flags for WASM
LDFLAGS_WASM = -lwasi-emulated-process-clocks

# ===============================
# Targets
# ===============================

all: native wasm

native: $(SRC)
	$(CC_NATIVE) $(CFLAGS_NATIVE) -o $(NATIVE) $(SRC)

wasm: $(SRC)
	$(CC_WASM) $(CFLAGS_WASM) -o $(WASM) $(SRC) $(LDFLAGS_WASM) --sysroot=$(SYSROOT_WASM)

clean:
	rm -f $(NATIVE) $(WASM)

.PHONY: all native wasm clean
