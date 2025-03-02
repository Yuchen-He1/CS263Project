#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <x86intrin.h>  // For __rdtsc()

// Get high-precision monotonic time in milliseconds
double getCurrentTimeMillis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);  // More accurate than CLOCK_REALTIME
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;  // Convert to ms
}

// Get CPU time in milliseconds
double getCPUTimeMillis() {
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);  // Process-specific CPU time
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;  // Convert to ms
}

// Get CPU cycle count
uint64_t getCPUCycles() {
    return __rdtsc();
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

    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    srand(42);  // Use fixed seed for reproducibility

    // Initialize array with random values
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    double startWallTime = getCurrentTimeMillis();
    double startCPUTime = getCPUTimeMillis();
    uint64_t startCycles = getCPUCycles();

    // Bubble Sort
    for (int i = 0; i < N - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < N - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    uint64_t endCycles = getCPUCycles();
    double endCPUTime = getCPUTimeMillis();
    double endWallTime = getCurrentTimeMillis();

    printf("N = %d\n", N);
    printf("Elapsed CPU Time: %.6f ms\n", (endCPUTime - startCPUTime));
    printf("Elapsed CPU Cycles: %llu\n", (endCycles - startCycles));

    free(arr);
    return 0;
}
