const { performance } = require('perf_hooks');
const fs = require('fs');

const benchmarks = [
    { file: 'bubble_sort.js', func: 'run_bubble_sort', sizes: [1000, 5000, 10000, 50000] },
    { file: 'fibonacci.js', func: 'run_fibonacci', sizes: [30, 32, 34, 36, 38, 40] },
    { file: 'hanoi.js', func: 'run_hanoi', sizes: [10, 15, 20, 22, 24, 25] },
    { file: 'matrix_multiplication.js', func: 'run_matrix_multiplication', sizes: [100, 200, 300, 400, 500] },
    { file: 'qsort.js', func: 'run_qsort', sizes: [1000, 5000, 10000, 50000, 100000] },
    { file: 'prime_sieve.js', func: 'run_prime_sieve', sizes: [100000, 500000, 1000000, 5000000] }
];

const csvFile = "wasm_results_c.csv";
fs.writeFileSync(csvFile, "Benchmark,Input Size,Time (ms)\n");

async function runWasmBenchmark(benchmarkFile, functionName, N) {
    try {
        const module = await import(`./WASM_Benchmark/${benchmarkFile}`); // Import WebAssembly module
        const instance = await module.default();

        console.log(`Running WebAssembly ${functionName} for N=${N}...`);

        const start = performance.now();
        const result = instance.ccall(functionName, 'number', ['number'], [N]);  // Call Wasm function
        const end = performance.now();

        const timeTaken = (end - start).toFixed(6);
        console.log(`WebAssembly ${functionName}(${N}) Result: ${result}`);
        console.log(`WebAssembly ${functionName} Time: ${timeTaken} ms\n`);

        // Append result to CSV
        fs.appendFileSync(csvFile, `${functionName},${N},${timeTaken}\n`);
    } catch (error) {
        console.error(`Error running ${functionName} for N=${N}:`, error);
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
