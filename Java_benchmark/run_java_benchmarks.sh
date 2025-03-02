#!/bin/bash

output_file="java_benchmark_results.txt"
echo "Java Benchmarks Performance Results (Wall Time)" > "$output_file"
echo "-------------------------------------------------" >> "$output_file"

# Compile Java programs
javac BubbleSortBenchmark.java FibonacciBenchmark.java HanoiBenchmark.java MatrixBenchmark.java QuickSortBenchmark.java PrimeSieveBenchmark.java

# Define input sizes
bubble_sizes=(1000 5000 10000 50000)
fibonacci_sizes=(30 32 34 36 38 40)
hanoi_sizes=(10 15 20 22 24 25)
matrix_sizes=(100 200 300 400 500)
qsort_sizes=(1000 5000 10000 50000 100000)
sieve_limits=(100000 500000 1000000 5000000)

# Function to run a Java benchmark
run_benchmark() {
    local class=$1
    local input_sizes=("${!2}")
    local benchmark_name=$3

    echo "Running $benchmark_name..."
    echo "Benchmark: $benchmark_name" >> "$output_file"
    for size in "${input_sizes[@]}"
    do
        echo "Running $benchmark_name with input size $size..."
        java "$class" "$size" >> "$output_file"
    done
    echo "----------------------------------------" >> "$output_file"
}

# Run all benchmarks
run_benchmark "BubbleSortBenchmark" bubble_sizes[@] "Bubble Sort"
run_benchmark "FibonacciBenchmark" fibonacci_sizes[@] "Fibonacci"
run_benchmark "HanoiBenchmark" hanoi_sizes[@] "Tower of Hanoi"
run_benchmark "MatrixBenchmark" matrix_sizes[@] "Matrix Multiplication"
run_benchmark "QuickSortBenchmark" qsort_sizes[@] "QuickSort"
run_benchmark "PrimeSieveBenchmark" sieve_limits[@] "Prime Number Sieve"

echo "All Java benchmarks completed. Results saved to $output_file."
