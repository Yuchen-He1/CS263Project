#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <x86intrin.h>  // For __rdtsc()

long getCurrentTimeMillis() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

// Function to get CPU time in nanoseconds
long getCPUTimeNanos() {
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return (long)(ts.tv_sec * 1000000000L + ts.tv_nsec);
}

// Function to read CPU cycle counter (x86 only)
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

    // Initialize array with random values
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    long startWallTime = getCurrentTimeMillis();
    long startCPUTime = getCPUTimeNanos();
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
    long endCPUTime = getCPUTimeNanos();
    long endWallTime = getCurrentTimeMillis();

    printf("N = %d\n", N);
    printf("Elapsed Wall Time: %ld ms\n", (endWallTime - startWallTime));
    printf("Elapsed CPU Time: %ld ns (%.2f ms)\n", (endCPUTime - startCPUTime), (endCPUTime - startCPUTime) / 1e6);
    printf("Elapsed CPU Cycles: %llu\n", (endCycles - startCycles));

    free(arr);
    return 0;
}
