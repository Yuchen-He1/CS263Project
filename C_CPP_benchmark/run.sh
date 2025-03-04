#!/bin/bash
# run_benchmarks.sh
# This script concurrently runs all benchmarks located in the 'bin/' directory.
# It supports four variants: C native, C WASM, CPP native, and CPP WASM.
# Each benchmark is executed multiple times (NUM_RUNS) and the average execution time (in milliseconds) is computed.
# The results are saved in a CSV file (results.csv).
# WASM benchmarks are executed using an absolute path to wasmtime.
#
# Note: All benchmark outputs are converted and saved in milliseconds.

# Number of runs for each benchmark
NUM_RUNS=5

# Absolute path to WASMTIME; adjust as necessary
WASMTIME="/home/hylanc/.wasmtime/bin/wasmtime"

# CSV output file
CSV_FILE="results.csv"

# Initialize the CSV file with a header (AverageTime in ms)
echo "Benchmark,Variant,AverageTime(ms)" > "$CSV_FILE"

# Define the file suffix for each variant and the corresponding command.
declare -A VARIANT_SUFFIX
declare -A VARIANT_CMD
VARIANT_SUFFIX["C_native"]="_c_native.out"
VARIANT_SUFFIX["C_wasm"]="_c_wasm.wasm"
VARIANT_SUFFIX["CPP_native"]="_cpp_native.out"
VARIANT_SUFFIX["CPP_wasm"]="_cpp_wasm.wasm"

VARIANT_CMD["C_native"]=""
VARIANT_CMD["CPP_native"]=""
VARIANT_CMD["C_wasm"]="$WASMTIME"
VARIANT_CMD["CPP_wasm"]="$WASMTIME"

# Temporary directory for concurrent execution outputs (if needed)
TMP_DIR="tmp_results"
mkdir -p "$TMP_DIR"

# Function: Run a single benchmark multiple times and compute the average execution time (in milliseconds).
# Parameters:
#   $1 - Full path to the benchmark file.
#   $2 - Variant (e.g., C_native, C_wasm, CPP_native, CPP_wasm).
# The result is appended to the CSV file.
run_benchmark() {
    local filepath="$1"
    local variant="$2"
    local suffix="${VARIANT_SUFFIX[$variant]}"
    
    # Extract the benchmark name by removing the 'bin/' prefix and the variant-specific suffix.
    local rel_path="${filepath#bin/}"
    local bench_name="${rel_path%$suffix}"
    # Remove any .c or .cpp extension if present.
    bench_name="${bench_name%.c}"
    bench_name="${bench_name%.cpp}"
    
    local cmd_prefix=${VARIANT_CMD[$variant]}
    local total=0
    local count=0

    # Run the benchmark NUM_RUNS times and parse the output for the time.
    # The output must include "Time:" followed by a number and a unit (ms or s).
    for (( i=1; i<=NUM_RUNS; i++ )); do
        if [ -n "$cmd_prefix" ]; then
            output=$("$cmd_prefix" "$filepath")
        else
            output=$("$filepath")
        fi

        # Extract the numeric value and unit from the output using regex.
        if [[ "$output" =~ Time:\ ([0-9.]+)\ (ms|s) ]]; then
            value="${BASH_REMATCH[1]}"
            unit="${BASH_REMATCH[2]}"
            if [ "$unit" == "ms" ]; then
                time_ms="$value"
            else
                # Convert seconds to milliseconds
                time_ms=$(awk "BEGIN {printf \"%.6f\", $value * 1000}")
            fi
            total=$(awk "BEGIN {printf \"%.6f\", $total + $time_ms}")
            ((count++))
        else
            echo "Warning: Unable to parse time output. Output: $output"
        fi
    done

    if [ $count -gt 0 ]; then
        avg=$(awk "BEGIN {printf \"%.6f\", $total / $count}")
    else
        avg="0"
    fi

    # Append the benchmark result to the CSV file (format: Benchmark,Variant,AverageTime(ms))
    echo "${bench_name},${variant},${avg}" >> "$CSV_FILE"
    echo "Completed $bench_name ($variant): Average Time = ${avg} ms"
}

# Function: Run all benchmarks concurrently.
# For each variant, recursively search the 'bin/' directory for files matching the variant-specific suffix.
run_all() {
    for variant in "${!VARIANT_SUFFIX[@]}"; do
        suffix="${VARIANT_SUFFIX[$variant]}"
        # Recursively find matching benchmark files.
        files=$(find bin -type f -name "*${suffix}")
        for f in $files; do
            # Run each benchmark in the background.
            run_benchmark "$f" "$variant" &
        done
    done
    wait
}

echo "Running benchmarks concurrently..."
run_all

echo "All benchmarks completed. Results saved in $CSV_FILE."
