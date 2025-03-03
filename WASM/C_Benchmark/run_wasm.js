const { performance } = require('perf_hooks');

async function runWasmBenchmark(N) {
    const module = await import('./bubble_sort.js'); // Import WebAssembly module
    const instance = await module.default();

    console.log(`Running WebAssembly Bubble Sort for N=${N}...`);

    const start = performance.now();
    instance.ccall('run_bubble_sort', null, ['number'], [N]);  // Call Wasm function
    const end = performance.now();

    console.log(`WebAssembly Bubble Sort Time: ${(end - start).toFixed(6)} ms`);
}

// Run WebAssembly benchmark for different input sizes
async function benchmark() {
    const inputSizes = [1000, 5000, 10000, 50000];
    for (let N of inputSizes) {
        await runWasmBenchmark(N);
    }
}

benchmark();
