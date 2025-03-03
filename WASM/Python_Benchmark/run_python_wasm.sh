#!/bin/bash

# Ensure Node.js is installed
if ! command -v node &> /dev/null; then
    echo "Error: Node.js is not installed. Install it first."
    exit 1
fi

# Define output file
OUTPUT_FILE="bubble_sort_wasm_results.csv"
echo "Benchmark,Input Size,Time (ms)" > "$OUTPUT_FILE"

# Define Python benchmark directory
PYTHON_BENCHMARKS_DIR="./"
SCRIPT_NAME="bubble_sort_wasm.py"

# Define input sizes for Bubble Sort
INPUT_SIZES="10, 50, 100, 500"

# Ensure Pyodide is downloaded correctly
PYODIDE_DIR="./pyodide_local"
if [ ! -d "$PYODIDE_DIR" ]; then
    echo "Downloading Pyodide..."
    mkdir -p "$PYODIDE_DIR"
    cd "$PYODIDE_DIR"
    wget -q https://cdn.jsdelivr.net/pyodide/v0.23.4/full/pyodide.mjs
    wget -q https://cdn.jsdelivr.net/pyodide/v0.23.4/full/pyodide.asm.js
    wget -q https://cdn.jsdelivr.net/pyodide/v0.23.4/full/pyodide.asm.wasm
    cd ..
fi

# Create the JavaScript script dynamically (ES Module `.mjs`)
cat <<EOF > run_bubble_sort_wasm.mjs
import { loadPyodide } from "./pyodide_local/pyodide.mjs";  // Use local Pyodide module
import fs from "fs";
import path from "path";

const PYTHON_BENCHMARKS_DIR = "./$PYTHON_BENCHMARKS_DIR";
const scriptName = "$SCRIPT_NAME";
const inputSizes = [$INPUT_SIZES];
const outputFile = "$OUTPUT_FILE";

async function runPythonWasm(scriptName, inputSize) {
    let pyodide = await loadPyodide({
        indexURL: "./pyodide_local/"
    });

    const scriptPath = path.join(PYTHON_BENCHMARKS_DIR, scriptName);
    const script = fs.readFileSync(scriptPath, "utf8");

    await pyodide.runPythonAsync(script);
    
    const start = performance.now();
    const result = pyodide.runPython(\`run_bubble_sort(\${inputSize})\`);
    const end = performance.now();
    
    const executionTime = (end - start).toFixed(6); // Time in ms
    console.log(\`Python WASM | \${scriptName} | Input: \${inputSize} | Time: \${executionTime} ms\`);
    
    fs.appendFileSync(outputFile, \`\${scriptName},\${inputSize},\${executionTime}\n\`);
}

async function runBubbleSortBenchmark() {
    for (let size of inputSizes) {
        await runPythonWasm(scriptName, size);
    }
}

runBubbleSortBenchmark();
EOF

# Run the script in Node.js
echo "Running Python Bubble Sort WebAssembly Benchmark..."
node run_bubble_sort_wasm.mjs

echo "Bubble Sort WebAssembly benchmark completed!"
echo "Results saved in $OUTPUT_FILE."
