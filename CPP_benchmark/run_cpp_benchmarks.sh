#!/bin/bash

# Output file
output_file="cpp_benchmark_results.txt"
echo "C++ Benchmarks Performance Results (Wall Time, CPU Time, Cycles)" > "$output_file"
echo "----------------------------------------------------------------" >> "$output_file"

# Compile all C++ programs with optimizations
echo "Compiling all C++ benchmarks..."
g++ -std=c++11 -O2 -o bubble_sort_benchmark bubble_sort_benchmark.cpp
g++ -std=c++11 -O2 -o fibonacci_benchmark fibonacci_benchmark.cpp
g++ -std=c++11 -O2 -o hanoi_benchmark hanoi_benchmark.cpp
g++ -std=c++11 -O2 -o matrix_benchmark matrix_benchmark.cpp
g++ -std=c++11 -O2 -o qsort_benchmark qsort_benchmark.cpp
g++ -std=c++11 -O2 -o prime_sieve_benchmark prime_sieve_benchmark.cpp
echo "Compilation completed."

# Define input sizes for each benchmark
bubble_sizes=(1000 5000 10000 50000)
fibonacci_sizes=(30 32 34 36 38 40)
hanoi_sizes=(10 15 20 22 24 25)
matrix_sizes=(100 200 300 400 500)
qsort_sizes=(1000 5000 10000 50000 100000)
sieve_limits=(100000 500000 1000000 5000000)

# Function to run a benchmark and append results
run_benchmark() {
    local program=$1
    local input_sizes=("${!2}")
    local benchmark_name=$3

    echo "Running $benchmark_name..."
    echo "Benchmark: $benchmark_name" >> "$output_file"
    for size in "${input_sizes[@]}"
    do
        echo "Running $benchmark_name with input size $size..."
        ./$program "$size" >> "$output_file"
    done
    echo "----------------------------------------" >> "$output_file"
}

# Run all benchmarks
run_benchmark "bubble_sort_benchmark" bubble_sizes[@] "Bubble Sort"
run_benchmark "fibonacci_benchmark" fibonacci_sizes[@] "Fibonacci"
run_benchmark "hanoi_benchmark" hanoi_sizes[@] "Tower of Hanoi"
run_benchmark "matrix_benchmark" matrix_sizes[@] "Matrix Multiplication"
run_benchmark "qsort_benchmark" qsort_sizes[@] "QuickSort"
run_benchmark "prime_sieve_benchmark" sieve_limits[@] "Prime Number Sieve"

echo "All C++ benchmarks completed. Results saved to $output_file."
