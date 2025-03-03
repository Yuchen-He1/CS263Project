import { loadPyodide } from "pyodide";
import fs from "fs";
import path from "path";

const PYTHON_BENCHMARKS_DIR = "./";
const outputFile = "python_wasm_results.csv";

// Define all benchmarks dynamically
// const benchmarks = [
//     { script: "bubble_sort_wasm.py", func: "run_bubble_sort", sizes: [10, 50, 100, 500] },
//     { script: "fibonacci_wasm.py", func: "run_fibonacci", sizes: [10, 15, 20, 25, 30, 35, 40] }
// ];

const benchmarks = [
    { script: 'bubble_sort_wasm.py', func: 'run_bubble_sort', sizes: [1000, 5000, 10000, 50000] },
    { script: 'fibonacci_wasm.py', func: 'run_fibonacci', sizes: [30, 32, 34, 36, 38, 40] },
    { script: 'hanoi_wasm.py', func: 'run_hanoi', sizes: [10, 15, 20, 22, 24, 25] },
    { script: 'matrix_multiplication_wasm.py', func: 'run_matrix_multiplication', sizes: [100, 200, 300, 400, 500] },
    { script: 'qsort_wasm.py', func: 'run_qsort', sizes: [1000, 5000, 10000, 50000, 100000] },
    { script: 'prime_sieve_wasm.py', func: 'run_prime_sieve', sizes: [100000, 500000, 1000000, 5000000] }
];

// Initialize CSV file with headers if it doesn't exist
if (!fs.existsSync(outputFile)) {
    fs.writeFileSync(outputFile, "Benchmark,Function,Input Size,Time (ms)\n");
}

async function runPythonWasm(scriptName, functionName, inputSize) {
    let pyodide = await loadPyodide();

    const scriptPath = path.join(PYTHON_BENCHMARKS_DIR, scriptName);
    const script = fs.readFileSync(scriptPath, "utf8");

    await pyodide.runPythonAsync(script); // Load the script

    // Measure execution time
    const start = performance.now();
    const result = pyodide.runPython(`${functionName}(${inputSize})`);
    const end = performance.now();

    const executionTime = (end - start).toFixed(6); // Time in ms
    console.log(`Python WASM | ${scriptName} | ${functionName}(${inputSize}) | Time: ${executionTime} ms`);

    // Append result to CSV file
    fs.appendFileSync(outputFile, `${scriptName},${functionName},${inputSize},${executionTime}\n`);
}

async function runAllBenchmarks() {
    for (let bench of benchmarks) {
        for (let size of bench.sizes) {
            await runPythonWasm(bench.script, bench.func, size);
        }
    }
}

runAllBenchmarks();
