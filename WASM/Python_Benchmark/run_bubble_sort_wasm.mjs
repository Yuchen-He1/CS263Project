import { loadPyodide } from "pyodide";
import fs from "fs";
import path from "path";

// Define benchmark settings
const PYTHON_BENCHMARKS_DIR = "./";
const scriptName = "bubble_sort_wasm.py";
const inputSizes = [10, 50, 100, 500]; // Test with small inputs for debugging

async function runPythonWasm(scriptName, inputSize) {
    let pyodide = await loadPyodide();
    const scriptPath = path.join(PYTHON_BENCHMARKS_DIR, scriptName);
    const script = fs.readFileSync(scriptPath, "utf8");

    await pyodide.runPythonAsync(script); // Load the script
    const sortedArray = pyodide.runPython(`run_bubble_sort(${inputSize})`); // Call function
    
    console.log(`Python WASM | ${scriptName} | Input: ${inputSize} | Sorted Array: ${sortedArray}`);
}

async function runBubbleSortBenchmark() {
    for (let size of inputSizes) {
        await runPythonWasm(scriptName, size);
    }
}

runBubbleSortBenchmark();
