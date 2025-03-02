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

// Function to allocate memory for a matrix
double** allocate_matrix(int N) {
    double** matrix = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double*)malloc(N * sizeof(double));
    }
    return matrix;
}

// Function to initialize a matrix with random values
void initialize_matrix(double** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

// Function to multiply two matrices
void multiply_matrices(double** A, double** B, double** C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to free allocated memory for a matrix
void free_matrix(double** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Invalid matrix size.\n");
        return 1;
    }

    // Allocate matrices
    double** A = allocate_matrix(N);
    double** B = allocate_matrix(N);
    double** C = allocate_matrix(N);

    // Initialize matrices
    initialize_matrix(A, N);
    initialize_matrix(B, N);

    double start_wall, end_wall, start_cpu, end_cpu;
    uint64_t start_cycles, end_cycles;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    start_cycles = get_cpu_cycles();

    multiply_matrices(A, B, C, N);

    end_cycles = get_cpu_cycles();
    end_cpu = get_cpu_time();
    end_wall = get_wall_time();

    printf("Matrix Size: %d x %d\n", N, N);
    printf("Wall Time: %.2f ms\n", (end_wall - start_wall) * 1000);
    printf("CPU Time: %.2f ms\n", (end_cpu - start_cpu) * 1000);
    printf("CPU Cycles: %llu\n", (end_cycles - start_cycles));

    // Free allocated memory
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
