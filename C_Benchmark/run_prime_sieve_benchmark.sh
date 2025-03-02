#!/bin/bash

# Compile with optimizations
gcc prime_sieve_benchmark.c -o prime_sieve_benchmark -O2 -march=native

# List of upper limits to test
limits=(100000 500000 1000000 5000000 10000000 50000000)

# Output file
output_file="prime_sieve_benchmark_results.txt"
echo "Prime Number Sieve Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "-------------------------------------------------------------------" >> "$output_file"

# Run tests
for N in "${limits[@]}"
do
    echo "Running Prime Number Sieve for N = $N..."
    ./prime_sieve_benchmark "$N" >> "$output_file"
done

echo "Benchmark completed. Results saved to $output_file."
