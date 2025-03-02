#!/bin/bash

# Compile with optimizations
gcc qsort_benchmark.c -o qsort_benchmark -O2 -march=native

# List of array sizes to test
sizes=(1000 5000 10000 50000 100000 500000 1000000)

# Output file
output_file="qsort_benchmark_results.txt"
echo "QuickSort Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "--------------------------------------------------------" >> "$output_file"

# Run tests
for N in "${sizes[@]}"
do
    echo "Running QuickSort for N = $N..."
    ./qsort_benchmark "$N" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
