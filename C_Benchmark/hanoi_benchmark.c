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

// Simulate moving a disk (no actual output to avoid slowdowns)
void moveDisk(int n, char from, char to) {
    // printf("Move disk %d from %c to %c\n", n, from, to); // Commented out to avoid performance impact
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

    double start_wall, end_wall, start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    hanoi(n, 'A', 'B', 'C');

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();
    end_wall = get_wall_time();

    printf("Hanoi(%d) completed.\n", n);
    printf("Wall Time: %.2f ms\n", (end_wall - start_wall) * 1000);
    printf("CPU Time: %.2f ms\n", (end_cpu - start_cpu) * 1000);
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    return 0;
}
