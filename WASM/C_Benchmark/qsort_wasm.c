#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>  // Required for WebAssembly compatibility

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to generate a random array
void generate_random_array(int *arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 10000;
    }
}

// WebAssembly-compatible entry point
EMSCRIPTEN_KEEPALIVE
void run_qsort(int N) {
    if (N <= 0) {
        return;  // Ignore invalid input
    }

    srand(42);  // Use fixed seed for reproducibility

    // Allocate memory for array
    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        return;  // Memory allocation failed
    }

    // Initialize array with random values
    generate_random_array(arr, N);

    // Sort the array using QuickSort
    qsort(arr, N, sizeof(int), compare);

    // Free allocated memory
    free(arr);
}
