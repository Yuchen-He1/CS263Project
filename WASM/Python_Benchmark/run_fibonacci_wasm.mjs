import { loadPyodide } from "pyodide";  // Load Pyodide WebAssembly runtime
import fs from "fs";
import path from "path";

const PYTHON_BENCHMARKS_DIR = "./";
const scriptName = "fibonacci_wasm.py";
const inputSizes = [10, 15, 20, 25, 30, 35, 40]; // Fibonacci indices

async function runPythonWasm(scriptName, inputSize) {
    let pyodide = await loadPyodide();

    const scriptPath = path.join(PYTHON_BENCHMARKS_DIR, scriptName);
    const script = fs.readFileSync(scriptPath, "utf8");

    await pyodide.runPythonAsync(script); // Load the script

    // Call `run_fibonacci(n)` inside WASM
    const result = pyodide.runPython(`run_fibonacci(${inputSize})`);
    
    console.log(`Python WASM | Fibonacci(${inputSize}) | Result: ${result}`);
}

async function runFibonacciBenchmark() {
    for (let size of inputSizes) {
        await runPythonWasm(scriptName, size);
    }
}

runFibonacciBenchmark();
