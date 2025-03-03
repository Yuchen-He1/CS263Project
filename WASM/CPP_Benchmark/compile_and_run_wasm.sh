#!/bin/bash

# Ensure Emscripten environment is sourced
source ../../emsdk/emsdk_env.sh || { echo "Failed to source Emscripten. Make sure emsdk is installed."; exit 1; }

# Define output directory
WASM_DIR="WASM_Benchmark"
mkdir -p $WASM_DIR

# Define CSV output file
CSV_FILE="wasm_results_cpp.csv"
echo "Benchmark,Input Size,Time (ms)" > "$CSV_FILE"  # CSV Header

# Define source files, corresponding JavaScript output files, and function names
C_FILES=("bubble_sort_wasm.cpp" "fibonacci_wasm.cpp" "hanoi_wasm.cpp" "matrix_multiplication_wasm.cpp" "qsort_wasm.cpp" "prime_sieve_wasm.cpp")
JS_FILES=("bubble_sort.js" "fibonacci.js" "hanoi.js" "matrix_multiplication.js" "qsort.js" "prime_sieve.js")
FUNCTION_NAMES=("_run_bubble_sort" "_run_fibonacci" "_run_hanoi" "_run_matrix_multiplication" "_run_qsort" "_run_prime_sieve")

# Define input sizes for each benchmark
declare -A INPUT_SIZES
INPUT_SIZES["bubble_sort.js"]="[1000, 5000, 10000, 50000]"
INPUT_SIZES["fibonacci.js"]="[30, 32, 34, 36, 38, 40]"


str="const benchmarks = [
    { file: 'bubble_sort.js', func: 'run_bubble_sort', sizes: [1000, 5000, 10000, 50000] },
    { file: 'fibonacci.js', func: 'run_fibonacci', sizes: [30, 32, 34, 36, 38, 40] },
    { file: 'hanoi.js', func: 'run_hanoi', sizes: [10, 15, 20, 22, 24, 25] },
    { file: 'matrix_multiplication.js', func: 'run_matrix_multiplication', sizes: [100, 200, 300, 400, 500] },
    { file: 'qsort.js', func: 'run_qsort', sizes: [1000, 5000, 10000, 50000, 100000] },
    { file: 'prime_sieve.js', func: 'run_prime_sieve', sizes: [100000, 500000, 1000000, 5000000] }
];"

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

# Create JavaScript runner for WebAssembly
cat <<EOF > run_wasm_benchmarks.js
const { performance } = require('perf_hooks');
const fs = require('fs');

$str

const csvFile = "$CSV_FILE";
fs.writeFileSync(csvFile, "Benchmark,Input Size,Time (ms)\\n");

async function runWasmBenchmark(benchmarkFile, functionName, N) {
    try {
        const module = await import(\`./WASM_Benchmark/\${benchmarkFile}\`); // Import WebAssembly module
        const instance = await module.default();

        console.log(\`Running WebAssembly \${functionName} for N=\${N}...\`);

        const start = performance.now();
        const result = instance.ccall(functionName, 'number', ['number'], [N]);  // Call Wasm function
        const end = performance.now();

        const timeTaken = (end - start).toFixed(6);
        console.log(\`WebAssembly \${functionName}(\${N}) Result: \${result}\`);
        console.log(\`WebAssembly \${functionName} Time: \${timeTaken} ms\\n\`);

        // Append result to CSV
        fs.appendFileSync(csvFile, \`\${functionName},\${N},\${timeTaken}\\n\`);
    } catch (error) {
        console.error(\`Error running \${functionName} for N=\${N}:\`, error);
    }
}

// Run WebAssembly benchmarks dynamically
async function benchmark() {
    for (let bench of benchmarks) {
        for (let N of bench.sizes) {
            await runWasmBenchmark(bench.file, bench.func, N);
        }
    }
}

benchmark();
EOF

echo "Running WebAssembly benchmarks..."
node run_wasm_benchmarks.js

echo "All WebAssembly benchmarks completed!"
echo "Results saved in $CSV_FILE"
