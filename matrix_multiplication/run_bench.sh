#!/usr/bin/env bash
#
# Run multiple benchmarks on matrix_mul_native vs. matrix_mul.wasm
# and collect timing data in results.csv.

OUTFILE="results.csv"
# Overwrite or create new file
echo "N,Run,NativeTime(s),Wasm3Time(s)" > "$OUTFILE"

# Define which matrix sizes you want to benchmark
SIZES="50 100 200 300 400 500"

# How many times to repeat each test for averaging
REPEATS=5

for N in $SIZES; do
  for i in $(seq 1 $REPEATS); do
    echo "Benchmarking with N=$N (run $i of $REPEATS)"

    # Time the native binary (capture just the "real" seconds)
    NATIVE_TIME=$(/usr/bin/time -f "%e" ./matrix_mul_native "$N" 2>&1)

    # Time the wasm3 execution
    WASM_TIME=$(/usr/bin/time -f "%e" wasm3 matrix_mul.wasm "$N" 2>&1)

    # Append to CSV: N, run_index, native_time, wasm3_time
    echo "$N,$i,$NATIVE_TIME,$WASM_TIME" >> "$OUTFILE"
  done
done

echo "Benchmark complete! Results saved in $OUTFILE"
