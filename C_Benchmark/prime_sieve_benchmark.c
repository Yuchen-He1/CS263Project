#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

    double start_wall, end_wall, start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    // Run the prime number sieve
    prime_sieve(N, prime);

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();
    end_wall = get_wall_time();

    printf("Prime Sieve Upper Limit: %d\n", N);
    printf("Wall Time: %.2f ms\n", (end_wall - start_wall) * 1000);
    printf("CPU Time: %.2f ms\n", (end_cpu - start_cpu) * 1000);
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    // Free allocated memory
    free(prime);

    return 0;
}
