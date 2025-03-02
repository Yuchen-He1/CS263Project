#!/bin/bash

# Compile with optimizations
gcc matrix_multiplication_benchmark.c -o matrix_benchmark -O2 -march=native

# List of matrix sizes to test
sizes=(100 200 300 400 500 600 700 800 900 1000)

# Output file
output_file="matrix_benchmark_results.txt"
echo "Matrix Multiplication Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "--------------------------------------------------------------------" >> "$output_file"

# Run tests
for N in "${sizes[@]}"
do
    echo "Running Matrix Multiplication for N = $N..."
    ./matrix_benchmark "$N" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
