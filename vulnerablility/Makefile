# Makefile for compiling vuln_stack.c and vuln_format.c to both
# Native Linux executables and WebAssembly (WASM) modules using WASI SDK

# ===============================
# Variables
# ===============================

# Compiler for Native Linux
CC_NATIVE = gcc

# Compiler for WASM (WASI SDK's Clang)
WASI_SDK_PATH = /home/hylanc/wasi-sdk-25.0-x86_64-linux
CC_WASM = $(WASI_SDK_PATH)/bin/clang

# WASI sysroot
SYSROOT_WASM = $(WASI_SDK_PATH)/share/wasi-sysroot

# Source files (you can add more if needed)
SRCS = vuln_stack.c vuln_format.c use_after_free.c vuln_overflow.c 	seg_fault.c

# Derived base names (without extension)
BASES = vuln_stack vuln_format use_after_free vuln_overflow seg_fault

# Suffixes for targets
NATIVE_SUFFIX = _native
WASM_SUFFIX = .wasm

# Compiler flags for native build
CFLAGS_NATIVE = -O0 -Wall -Wextra

# Compiler flags for WASM build
CFLAGS_WASM = --target=wasm32-wasi --sysroot=$(SYSROOT_WASM) -O0 \
              -D_WASI_EMULATED_PROCESS_CLOCKS -Wno-deprecated-declarations

# Linker flags for WASM build
LDFLAGS_WASM = -lwasi-emulated-process-clocks

# ===============================
# Targets
# ===============================

.PHONY: all native wasm clean

# Default target: build both native and wasm versions
all: native wasm

# Build all native executables
native: $(BASES:%=%$(NATIVE_SUFFIX))

# Build each native executable
%$(NATIVE_SUFFIX): %.c
	$(CC_NATIVE) $(CFLAGS_NATIVE) -o $@ $<

# Build all WASM modules
wasm: $(BASES:%=%$(WASM_SUFFIX))

# Build each WASM module
%$(WASM_SUFFIX): %.c
	$(CC_WASM) $(CFLAGS_WASM) -o $@ $< $(LDFLAGS_WASM)

# Clean up generated files
clean:
	rm -f $(BASES:%=%$(NATIVE_SUFFIX)) $(BASES:%=%$(WASM_SUFFIX))
