import { loadPyodide } from "pyodide";
import fs from "fs";
import path from "path";

const PYTHON_BENCHMARKS_DIR = "./Python_Benchmark";
const outputFile = "python_wasm_results.csv";

async function runPythonWasm(scriptName, inputSize) {
    let pyodide = await loadPyodide();
    const scriptPath = path.join(PYTHON_BENCHMARKS_DIR, scriptName);
    const script = fs.readFileSync(scriptPath, "utf8");

    await pyodide.runPythonAsync(script);
    const result = pyodide.runPython(`run_benchmark(${inputSize})`);
    
    console.log(`Python WASM | ${scriptName} | Input: ${inputSize} | Time: ${result} ms`);
    
    fs.appendFileSync(outputFile, `${scriptName},${inputSize},${result}\n`);
}

async function runAllBenchmarks() {
    const benchmarks = [
        { file: "hanoi_benchmark.py", sizes: [10 15 20 22 24 25] },
        { file: "matrix_benchmark.py", sizes: [100 200 300 400 500] },
        { file: "prime_sieve_benchmark.py", sizes: [100000 500000 1000000 5000000] },
        { file: "bubble_sort_benchmark.py", sizes: [1000 5000 10000 50000] },
        { file: "fibonacci_benchmark.py", sizes: [30 32 34 36 38 40] },
        { file: "qsort_benchmark.py", sizes: [1000 5000 10000 50000 100000] },
    ];
    
    for (let bench of benchmarks) {
        for (let size of bench.sizes) {
            await runPythonWasm(bench.file, size);
        }
    }
}

runAllBenchmarks();
