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

// Simulate moving a disk (no actual output to avoid slowdowns)
void moveDisk(int n, char from, char to) {
    // Placeholder function to simulate move without affecting performance
}

// Recursive Tower of Hanoi function
void hanoi(int n, char from, char aux, char to) {
    if (n == 1) {
        moveDisk(n, from, to);
        return;
    }
    hanoi(n - 1, from, to, aux);
    moveDisk(n, from, to);
    hanoi(n - 1, aux, from, to);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_disks>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1) {
        fprintf(stderr, "Invalid number of disks.\n");
        return 1;
    }

    double start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    hanoi(n, 'A', 'B', 'C');

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();

    printf("Hanoi(%d) completed.\n", n);
    printf("CPU Time: %.6f ms\n", end_cpu - start_cpu);
    printf("CPU Cycles: %llu\n", end_cycles - start_cycles);

    return 0;
}
