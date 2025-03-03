#!/bin/bash

# Ensure Emscripten environment is sourced
source ../../emsdk/emsdk_env.sh || { echo "Failed to source Emscripten. Make sure emsdk is installed."; exit 1; }

# Define output directory
WASM_DIR="WASM_Benchmark"
mkdir -p $WASM_DIR

# Define source files, corresponding JavaScript output files, and function names
C_FILES=("bubble_sort_wasm.c" "fibonacci_wasm.c")
JS_FILES=("bubble_sort.js" "fibonacci.js")
FUNCTION_NAMES=("_run_bubble_sort" "_run_fibonacci")

echo "Compiling C benchmarks to WebAssembly..."

# Compile each C file dynamically
for i in "${!C_FILES[@]}"; do
    c_file="${C_FILES[$i]}"
    js_output="$WASM_DIR/${JS_FILES[$i]}"
    function_name="${FUNCTION_NAMES[$i]}"

    echo "Compiling $c_file -> $js_output (Exporting: $function_name)..."

    emcc "$c_file" -o "$js_output" \
        -s MODULARIZE=1 \
        -s EXPORTED_FUNCTIONS="['$function_name', '_malloc']" \
        -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" \
        -s INITIAL_MEMORY=64MB -s MAXIMUM_MEMORY=512MB -s ALLOW_MEMORY_GROWTH=1 \
        -s ERROR_ON_UNDEFINED_SYMBOLS=0 || { echo "Compilation failed for $c_file"; exit 1; }
done

echo "WebAssembly compilation completed successfully!"
