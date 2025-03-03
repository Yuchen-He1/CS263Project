#!/bin/bash

# Output CSV file
output_file="wasm_vs_native_results.csv"
echo "Benchmark,Input Size,Native Time (ms),WebAssembly Time (ms)" > "$output_file"

# Define directories (following your folder structure)
C_DIR="C_Benchmark"
WASM_DIR="WASM_Benchmark"

# Define C benchmark files (without extension)
BENCHMARKS=("bubble_sort_benchmark" "fibonacci_benchmark" "hanoi_benchmark" "matrix_benchmark" "qsort_benchmark" "prime_sieve_benchmark")

# Define input sizes
bubble_sizes=(1000 5000 10000 50000)
fibonacci_sizes=(30 32 34 36 38 40)
hanoi_sizes=(10 15 20 22 24 25)
matrix_sizes=(100 200 300 400 500)
qsort_sizes=(1000 5000 10000 50000 100000)
sieve_limits=(100000 500000 1000000 5000000)

# Associate benchmarks with input sizes
declare -A INPUT_SIZES
INPUT_SIZES["bubble_sort_benchmark"]=bubble_sizes[@]
INPUT_SIZES["fibonacci_benchmark"]=fibonacci_sizes[@]
INPUT_SIZES["hanoi_benchmark"]=hanoi_sizes[@]
INPUT_SIZES["matrix_benchmark"]=matrix_sizes[@]
INPUT_SIZES["qsort_benchmark"]=qsort_sizes[@]
INPUT_SIZES["prime_sieve_benchmark"]=sieve_limits[@]

# Ensure WebAssembly output directory exists
mkdir -p $WASM_DIR

# Compile C benchmarks to WebAssembly with increased memory limits
echo "Compiling C benchmarks to WebAssembly..."
for benchmark in "${BENCHMARKS[@]}"; do
    emcc "$C_DIR/$benchmark.c" -o "$WASM_DIR/$benchmark.js" \
        -s MODULARIZE=1 -s EXPORTED_FUNCTIONS="['_main']" \
        -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" \
        -s INITIAL_MEMORY=64MB -s MAXIMUM_MEMORY=1GB -s ALLOW_MEMORY_GROWTH=1 \
        -s TOTAL_STACK=64MB
done

# Compile C benchmarks natively
echo "Compiling C benchmarks for native execution..."
for benchmark in "${BENCHMARKS[@]}"; do
    gcc -O2 "$C_DIR/$benchmark.c" -o "$C_DIR/$benchmark"
done

# Create a JavaScript file to run WebAssembly benchmarks
cat <<EOF > $WASM_DIR/run_wasm.js
const { performance } = require('perf_hooks');

async function runWasm(filename, input) {
    const module = await import(\`./\${filename}\`);
    const instance = await module.default();

    const start = performance.now();
    const result = instance.ccall('main', 'number', ['number'], [input]);
    const end = performance.now();

    return (end - start);
}

async function benchmarkWasm() {
    console.log("Running WebAssembly Benchmarks...");
    const inputSizes = [30, 32, 34, 36, 38, 40];
    const benchmarks = ["fibonacci_benchmark.js", "bubble_sort_benchmark.js", "hanoi_benchmark.js", "matrix_benchmark.js", "qsort_benchmark.js", "prime_sieve_benchmark.js"];

    let results = {};
    for (let i = 0; i < benchmarks.length; i++) {
        results[benchmarks[i]] = [];
        for (let size of inputSizes) {
            let time = await runWasm(benchmarks[i], size);
            results[benchmarks[i]].push({ size, time });
            console.log(\`\${benchmarks[i]} | Size: \${size} | Wasm Time: \${time.toFixed(6)} ms\`);
        }
    }

    return results;
}

benchmarkWasm().then(results => {
    const fs = require('fs');
    let csvContent = "Benchmark,Input Size,WebAssembly Time (ms)\\n";
    for (let benchmark in results) {
        results[benchmark].forEach(row => {
            csvContent += \`\${benchmark},\${row.size},\${row.time.toFixed(6)}\\n\`;
        });
    }
    fs.writeFileSync("wasm_results.csv", csvContent);
});
EOF

# Run benchmarks for Native and WebAssembly
echo "Running benchmarks..."
for benchmark in "${BENCHMARKS[@]}"; do
    input_sizes=("${!INPUT_SIZES[$benchmark]}")

    for size in "${input_sizes[@]}"; do
        echo "Running Native: $benchmark with size $size..."
        native_time=$("$C_DIR/$benchmark" "$size" 2>/dev/null | grep -o '[0-9.]* ms' | awk '{print $1}')
        
        echo "Running WebAssembly: $benchmark with size $size..."
        wasm_time=$(node "$WASM_DIR/run_wasm.js" | grep "$benchmark" | grep "$size" | awk '{print $6}')
        
        if [[ -z "$native_time" ]]; then native_time="N/A"; fi
        if [[ -z "$wasm_time" ]]; then wasm_time="N/A"; fi

        echo "$benchmark,$size,$native_time,$wasm_time" >> "$output_file"
    done
done

echo "All benchmarks completed. Results saved to $output_file."
