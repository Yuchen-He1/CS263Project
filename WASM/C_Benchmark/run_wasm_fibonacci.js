const { performance } = require('perf_hooks');

async function runWasmBenchmark(N) {
    const module = await import('./fibonacci.js'); // Import WebAssembly module
    const instance = await module.default();

    console.log(`Running WebAssembly Fibonacci for N=${N}...`);

    const start = performance.now();
    const result = instance.ccall('run_fibonacci', 'number', ['number'], [N]);  // Call Wasm function
    const end = performance.now();

    console.log(`WebAssembly Fibonacci(${N}) = ${result}`);
    console.log(`WebAssembly Fibonacci Time: ${(end - start).toFixed(6)} ms`);
}

// Run WebAssembly benchmark for different Fibonacci values
async function benchmark() {
    const inputSizes = [30, 32, 34, 36, 38, 40];
    for (let N of inputSizes) {
        await runWasmBenchmark(N);
    }
}

benchmark();
