const { performance } = require('perf_hooks');

async function runWasm(filename, input) {
    const module = await import(`./${filename}`);
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
            console.log(`${benchmarks[i]} | Size: ${size} | Wasm Time: ${time.toFixed(6)} ms`);
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
