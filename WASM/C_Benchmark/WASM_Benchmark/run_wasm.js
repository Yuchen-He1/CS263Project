const { performance } = require('perf_hooks');

async function runWasmBenchmark(benchmark, func, input) {
    const module = await import(`./${benchmark}`);
    const instance = await module.default();

    console.log(`Running WebAssembly ${benchmark} for input size ${input}...`);

    const start = performance.now();
    const result = instance.ccall(func, 'number', ['number'], [input]);  // Call Wasm function
    const end = performance.now();

    console.log(`WebAssembly ${benchmark} Time: ${(end - start).toFixed(6)} ms`);
    return end - start;
}

async function benchmarkWasm() {
    const inputSizes = {
        "bubble_sort.js": [1000, 5000, 10000, 50000],
        "fibonacci.js": [30, 32, 34, 36, 38, 40]
    };

    const functionNames = {
        "bubble_sort.js": "run_bubble_sort",
        "fibonacci.js": "run_fibonacci"
    };

    let results = {};
    for (let benchmark in inputSizes) {
        results[benchmark] = [];
        for (let size of inputSizes[benchmark]) {
            let time = await runWasmBenchmark(benchmark, functionNames[benchmark], size);
            results[benchmark].push({ size, time });
        }
    }

    return results;
}

benchmarkWasm().then(results => {
    const fs = require('fs');
    let csvContent = "Benchmark,Input Size,WebAssembly Time (ms)\n";
    for (let benchmark in results) {
        results[benchmark].forEach(row => {
            csvContent += `${benchmark},${row.size},${row.time.toFixed(6)}\n`;
        });
    }
    fs.writeFileSync("wasm_results.csv", csvContent);
});
