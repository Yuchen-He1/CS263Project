#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // clock_gettime()

// Recursive Fibonacci function (same as in C++)
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// High-precision timer (Equivalent to std::chrono::high_resolution_clock)
double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);  // High-resolution monotonic clock
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;  // Convert to milliseconds
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    double start = get_time_ms();
    long long result = fibonacci(n);
    double end = get_time_ms();

    printf("Fibonacci | N: %d | Result: %lld | Time: %.6f ms\n", n, result, (end - start));
    return 0;
}
