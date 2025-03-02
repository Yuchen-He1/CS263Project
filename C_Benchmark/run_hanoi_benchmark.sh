#!/bin/bash

# Compile with optimizations
gcc hanoi_benchmark.c -o hanoi_benchmark -O2 -march=native

# List of disk numbers to test
values=(10 15 20 22 24 25 26 27 28 29 30)

# Output file
output_file="hanoi_benchmark_results.txt"
echo "Tower of Hanoi Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "--------------------------------------------------------------" >> "$output_file"

# Run tests
for n in "${values[@]}"
do
    echo "Running Hanoi($n)..."
    ./hanoi_benchmark "$n" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
