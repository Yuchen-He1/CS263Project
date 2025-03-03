#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>  // Required for WebAssembly compatibility

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

// WebAssembly-compatible entry point
EMSCRIPTEN_KEEPALIVE
void run_matrix_multiplication(int N) {
    if (N <= 0) {
        return;  // Ignore invalid input
    }

    srand(42);  // Use fixed seed for reproducibility

    // Allocate matrices
    double** A = allocate_matrix(N);
    double** B = allocate_matrix(N);
    double** C = allocate_matrix(N);

    // Initialize matrices
    initialize_matrix(A, N);
    initialize_matrix(B, N);

    // Perform matrix multiplication
    multiply_matrices(A, B, C, N);

    // Free allocated memory
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
}
