#!/bin/bash

# Output CSV file
output_file="benchmark_results.csv"
echo "Language,Benchmark,Input Size,Time (ms)" > "$output_file"

# Define directories
C_DIR="C_Benchmark"
CPP_DIR="CPP_benchmark"
PYTHON_DIR="Python_benchmark"
JAVA_DIR="Java_benchmark"

# Compile C benchmarks
gcc -O2 -o $C_DIR/bubble_sort_c $C_DIR/bubble_sort_benchmark.c
gcc -O2 -o $C_DIR/fibonacci_c $C_DIR/fibonacci_benchmark.c
gcc -O2 -o $C_DIR/hanoi_c $C_DIR/hanoi_benchmark.c
gcc -O2 -o $C_DIR/matrix_c $C_DIR/matrix_benchmark.c
gcc -O2 -o $C_DIR/qsort_c $C_DIR/qsort_benchmark.c
gcc -O2 -o $C_DIR/prime_sieve_c $C_DIR/prime_sieve_benchmark.c

# Compile C++ benchmarks
g++ -O2 -o $CPP_DIR/bubble_sort_cpp $CPP_DIR/bubble_sort_benchmark.cpp
g++ -O2 -o $CPP_DIR/fibonacci_cpp $CPP_DIR/fibonacci_benchmark.cpp
g++ -O2 -o $CPP_DIR/hanoi_cpp $CPP_DIR/hanoi_benchmark.cpp
g++ -O2 -o $CPP_DIR/matrix_cpp $CPP_DIR/matrix_benchmark.cpp
g++ -O2 -o $CPP_DIR/qsort_cpp $CPP_DIR/qsort_benchmark.cpp
g++ -O2 -o $CPP_DIR/prime_sieve_cpp $CPP_DIR/prime_sieve_benchmark.cpp

# Compile Java benchmarks
javac -d $JAVA_DIR $JAVA_DIR/*.java || { echo "Java compilation failed!"; exit 1; }


# Define input sizes
bubble_sizes=(1000 5000 10000 50000)
fibonacci_sizes=(30 32 34 36 38 40)
hanoi_sizes=(10 15 20 22 24 25)
matrix_sizes=(100 200 300 400 500)
qsort_sizes=(1000 5000 10000 50000 100000)
sieve_limits=(100000 500000 1000000 5000000)

# Function to run a benchmark and append results to CSV
run_benchmark() {
    local language=$1
    local executable=$2

    if [[ "$language" == "Python" ]]; then 
        local input_sizes=("${!3}") 
    else 
        local -n input_sizes=$3
    fi
    # local input_sizes=("${!3}")
    # local -n input_sizes=$3  # Pass array by reference
    local benchmark_name=$4

    echo "Running $benchmark_name for $language..."
    for size in "${input_sizes[@]}"
    do
        echo "Running $benchmark_name with input size $size..."
        # if language == 'Python'; then 
        #      result=$($executable <<< $size 2>/dev/null | grep -o '[0-9.]* ms' | awk '{print $1}')  
        # fi
        # # result=$($executable "$size" 2>/dev/null | grep -o '[0-9.]* ms' | awk '{print $1}') 
        if [[ "$language" == "Python" ]]; then 
            result=$($executable <<< "$size" 2>/dev/null | grep -o '[0-9.]* ms' | awk '{print $1}')  
        else 
          result=$($executable "$size" 2>/dev/null | grep -o '[0-9.]* ms' | awk '{print $1}')
        fi

        echo $result
        if [[ -z "$result" ]]; then
            echo "Error running $benchmark_name ($language, size $size)" >&2
            result="N/A"
        fi
        echo "$language,$benchmark_name,$size,$result" >> "$output_file"
    done
}

# Run all benchmarks for C
run_benchmark "C" "$C_DIR/bubble_sort_c" bubble_sizes "Bubble Sort"
run_benchmark "C" "$C_DIR/fibonacci_c" fibonacci_sizes "Fibonacci"
run_benchmark "C" "$C_DIR/hanoi_c" hanoi_sizes "Tower of Hanoi"
run_benchmark "C" "$C_DIR/matrix_c" matrix_sizes "Matrix Multiplication"
run_benchmark "C" "$C_DIR/qsort_c" qsort_sizes "QuickSort"
run_benchmark "C" "$C_DIR/prime_sieve_c" sieve_limits "Prime Number Sieve"

# Run all benchmarks for C++
run_benchmark "C++" "$CPP_DIR/bubble_sort_cpp" bubble_sizes "Bubble Sort"
run_benchmark "C++" "$CPP_DIR/fibonacci_cpp" fibonacci_sizes "Fibonacci"
run_benchmark "C++" "$CPP_DIR/hanoi_cpp" hanoi_sizes "Tower of Hanoi"
run_benchmark "C++" "$CPP_DIR/matrix_cpp" matrix_sizes "Matrix Multiplication"
run_benchmark "C++" "$CPP_DIR/qsort_cpp" qsort_sizes "QuickSort"
run_benchmark "C++" "$CPP_DIR/prime_sieve_cpp" sieve_limits "Prime Number Sieve"

# Run all benchmarks for Python
run_benchmark "Python" "python3 $PYTHON_DIR/bubble_sort_benchmark.py" bubble_sizes[@] "Bubble Sort"
run_benchmark "Python" "python3 $PYTHON_DIR/fibonacci_benchmark.py" fibonacci_sizes[@] "Fibonacci"
run_benchmark "Python" "python3 $PYTHON_DIR/hanoi_benchmark.py" hanoi_sizes[@] "Tower of Hanoi"
run_benchmark "Python" "python3 $PYTHON_DIR/matrix_benchmark.py" matrix_sizes[@] "Matrix Multiplication"
run_benchmark "Python" "python3 $PYTHON_DIR/qsort_benchmark.py" qsort_sizes[@] "QuickSort"
run_benchmark "Python" "python3 $PYTHON_DIR/prime_sieve_benchmark.py" sieve_limits[@] "Prime Number Sieve"

# Run all benchmarks for Java
run_benchmark "Java" "java -cp $JAVA_DIR BubbleSortBenchmark" bubble_sizes "Bubble Sort"
run_benchmark "Java" "java -cp $JAVA_DIR FibonacciBenchmark" fibonacci_sizes "Fibonacci"
run_benchmark "Java" "java -cp $JAVA_DIR HanoiBenchmark" hanoi_sizes "Tower of Hanoi"
run_benchmark "Java" "java -cp $JAVA_DIR MatrixBenchmark" matrix_sizes "Matrix Multiplication"
run_benchmark "Java" "java -cp $JAVA_DIR QuickSortBenchmark" qsort_sizes "QuickSort"
run_benchmark "Java" "java -cp $JAVA_DIR PrimeSieveBenchmark" sieve_limits "Prime Number Sieve"

echo "All benchmarks completed. Results saved to $output_file."
