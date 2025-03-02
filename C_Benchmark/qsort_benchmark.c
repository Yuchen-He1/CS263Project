#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday()
#include <sys/times.h>  // times()
#include <unistd.h>     // sysconf()
#include <stdint.h>     // uint64_t
#include <x86intrin.h>  // __rdtsc()

// Get wall clock time in seconds
double get_wall_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

// Get CPU time in seconds
double get_cpu_time() {
    struct tms time_sample;
    clock_t clock_time = times(&time_sample);
    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    return (double)clock_time / ticks_per_sec;
}

// Get CPU cycle count
uint64_t get_cpu_cycles() {
    return __rdtsc();
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to generate random array
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

    // Allocate memory for array
    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Initialize array with random values
    generate_random_array(arr, N);

    double start_wall, end_wall, start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    // Sort the array using QuickSort
    qsort(arr, N, sizeof(int), compare);

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();
    end_wall = get_wall_time();

    printf("Array Size: %d\n", N);
    printf("Wall Time: %.2f ms\n", (end_wall - start_wall) * 1000);
    printf("CPU Time: %.2f ms\n", (end_cpu - start_cpu) * 1000);
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    // Free allocated memory
    free(arr);

    return 0;
}
