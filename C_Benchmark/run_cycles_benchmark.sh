#!/bin/bash

# Compile the program with optimizations
gcc bubble_sort_cycles.c -o bubble_sort_cycles -O2 -march=native

# List of array sizes to test
sizes=(1000 5000 10000 20000 50000 75000 100000 150000)

# Output file
output_file="bubble_sort_cycles_results.txt"
echo "Bubble Sort Performance Results (CPU Time & Cycles)" > "$output_file"
echo "--------------------------------------------------" >> "$output_file"

# Run the program for different sizes
for size in "${sizes[@]}"
do
    echo "Running for N = $size..."
    ./bubble_sort_cycles "$size" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
