#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // clock_gettime()
#include <stdint.h>     // uint64_t
#include <x86intrin.h>  // __rdtsc()

// Get high-precision monotonic time in milliseconds
double get_wall_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);  // More accurate than gettimeofday()
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;  // Convert to ms
}

// Get CPU time in milliseconds
double get_cpu_time() {
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);  // Process-specific CPU time
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;  // Convert to ms
}

// Get CPU cycle count
uint64_t get_cpu_cycles() {
    return __rdtsc();
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to generate a random array
void generate_random_array(int *arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 10000;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Invalid array size.\n");
        return 1;
    }

    srand(42);  // Use fixed seed for reproducibility

    // Allocate memory for array
    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Initialize array with random values
    generate_random_array(arr, N);

    double start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    // Sort the array using QuickSort
    qsort(arr, N, sizeof(int), compare);

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();

    printf("Array Size: %d\n", N);
    printf("CPU Time: %.6f ms\n", (end_cpu - start_cpu));
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    // Free allocated memory
    free(arr);

    return 0;
}
