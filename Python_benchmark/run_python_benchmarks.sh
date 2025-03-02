#!/bin/bash

output_file="python_benchmark_results.txt"
echo "Python Benchmarks Performance Results (Wall Time)" > "$output_file"
echo "-------------------------------------------------" >> "$output_file"

# Define input sizes for each benchmark
bubble_sizes=(1000 5000 10000 50000)
fibonacci_sizes=(30 32 34 36 38 40)
hanoi_sizes=(10 15 20 22 24 25)
matrix_sizes=(100 200 300 400 500)
qsort_sizes=(1000 5000 10000 50000 100000)
sieve_limits=(100000 500000 1000000 5000000)

# Function to run a benchmark and append results
run_benchmark() {
    local script=$1
    local input_sizes=("${!2}")
    local benchmark_name=$3

    echo "Running $benchmark_name..."
    echo "Benchmark: $benchmark_name" >> "$output_file"
    for size in "${input_sizes[@]}"
    do
        echo "Running $benchmark_name with input size $size..."
        python3 "$script" <<< "$size" >> "$output_file"
    done
    echo "----------------------------------------" >> "$output_file"
}

# Run all benchmarks
run_benchmark "bubble_sort_benchmark.py" bubble_sizes[@] "Bubble Sort"
run_benchmark "fibonacci_benchmark.py" fibonacci_sizes[@] "Fibonacci"
run_benchmark "hanoi_benchmark.py" hanoi_sizes[@] "Tower of Hanoi"
run_benchmark "matrix_benchmark.py" matrix_sizes[@] "Matrix Multiplication"
run_benchmark "qsort_benchmark.py" qsort_sizes[@] "QuickSort"
run_benchmark "prime_sieve_benchmark.py" sieve_limits[@] "Prime Number Sieve"

echo "All Python benchmarks completed. Results saved to $output_file."
