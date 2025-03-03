const { performance } = require('perf_hooks');

const benchmarks = [
    { file: 'bubble_sort.js', func: 'run_bubble_sort', sizes: [1000, 5000, 10000, 50000] },
    { file: 'fibonacci.js', func: 'run_fibonacci', sizes: [30, 32, 34, 36, 38, 40] }
];

async function runWasmBenchmark(benchmarkFile, functionName, N) {
    try {
        const module = await import(`./WASM_Benchmark/${benchmarkFile}`); // Import WebAssembly module
        const instance = await module.default();

        console.log(`Running WebAssembly ${functionName} for N=${N}...`);

        const start = performance.now();
        const result = instance.ccall(functionName, 'number', ['number'], [N]);  // Call Wasm function
        const end = performance.now();

        console.log(`WebAssembly ${functionName}(${N}) Result: ${result}`);
        console.log(`WebAssembly ${functionName} Time: ${(end - start).toFixed(6)} ms\n`);
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
