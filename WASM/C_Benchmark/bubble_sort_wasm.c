#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <emscripten.h>  // Emscripten-specific functions

// Bubble Sort Function
EMSCRIPTEN_KEEPALIVE
void bubble_sort(int *arr, int N) {
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
}

// Entry point for WebAssembly
EMSCRIPTEN_KEEPALIVE
void run_bubble_sort(int N) {
    if (N <= 0) {
        printf("Invalid array size.\n");
        return;
    }

    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return;
    }

    srand(42);  // Use fixed seed for reproducibility

    // Initialize array with random values
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    bubble_sort(arr, N);  // Run Bubble Sort

    free(arr);
}

// Main function (used for native execution)
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    run_bubble_sort(N);
    return 0;
}
