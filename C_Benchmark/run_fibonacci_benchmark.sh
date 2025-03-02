#!/bin/bash

# Compile with optimizations
gcc fibonacci_benchmark.c -o fibonacci_benchmark -O2 -march=native

# Fibonacci numbers to test
values=(30 32 34 36 38 40 42 44)

# Output file
output_file="fibonacci_benchmark_results.txt"
echo "Fibonacci Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "-----------------------------------------------------------" >> "$output_file"

# Run tests
for n in "${values[@]}"
do
    echo "Running Fibonacci($n)..."
    ./fibonacci_benchmark "$n" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
