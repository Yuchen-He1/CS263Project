#!/bin/bash
# compare_branch_count.sh
# This script compares the number of branch instructions
# in the disassembled output of a native executable and a WebAssembly module.
#
# Requirements:
# - For native disassembly: objdump must be available.
# - For WebAssembly disassembly: wasm-objdump (from the WABT tools) must be installed.
#
# Usage:
#   ./compare_branch_count.sh <native_executable> <wasm_file>

if [ $# -ne 2 ]; then
    echo "Usage: $0 <native_executable> <wasm_file>"
    exit 1
fi

NATIVE_EXE=$1
WASM_FILE=$2

echo "========================================"
echo "Disassembling native executable: $NATIVE_EXE"
echo "----------------------------------------"
# Count branch instructions in native disassembly.
# This regular expression looks for typical branch mnemonics.
native_branch_count=$(objdump -d "$NATIVE_EXE" | grep -E "\b(jmp|je|jne|jg|jge|jl|jle|ja|jae|jb|jbe|jz|jnz)\b" | wc -l)
echo "Native branch count: $native_branch_count"
echo "========================================"
echo ""

echo "========================================"
echo "Disassembling WASM module: $WASM_FILE"
echo "----------------------------------------"
# Count branch instructions in WebAssembly disassembly.
# WebAssembly branch instructions include: br, br_if, br_table.
wasm_branch_count=$(wasm-objdump -d "$WASM_FILE" | grep -E "\b(br|br_if|br_table)\b" | wc -l)
echo "WASM branch count: $wasm_branch_count"
echo "========================================"
