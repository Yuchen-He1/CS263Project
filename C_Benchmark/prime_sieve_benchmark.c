#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// Prime number sieve function
void prime_sieve(int N, bool *prime) {
    for (int i = 0; i <= N; i++) {
        prime[i] = true;
    }
    prime[0] = prime[1] = false;

    for (int p = 2; p * p <= N; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= N; i += p) {
                prime[i] = false;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <upper_limit>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 1) {
        fprintf(stderr, "Invalid upper limit.\n");
        return 1;
    }

    // Allocate memory for prime number array
    bool *prime = (bool*)malloc((N + 1) * sizeof(bool));
    if (!prime) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    double start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    // Run the prime number sieve
    prime_sieve(N, prime);

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();

    printf("Prime Sieve Upper Limit: %d\n", N);
    printf("CPU Time: %.6f ms\n", (end_cpu - start_cpu));
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    // Free allocated memory
    free(prime);

    return 0;
}
