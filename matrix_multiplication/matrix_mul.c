#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to free allocated memory
void freeMatrix(int **matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);

    // Allocate memory for matrices
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
        
        // Check if memory allocation was successful
        if (A[i] == NULL || B[i] == NULL || C[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }

    // Initialize matrices A and B with random values
    srand(time(NULL));  // Initialize random seed
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;  // Random values between 0-9
            B[i][j] = rand() % 10;
        }
    }

    //printf("\nMatrix A:\n");
    //printMatrix(A, N);
    //printf("\nMatrix B:\n");
    //printMatrix(B, N);

    // Start timing
    clock_t start = clock();

    // Perform matrix multiplication
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End timing
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //printf("\nResultant Matrix C:\n");
    //printMatrix(C, N);
    //printf("\nExecution time: %f seconds\n", cpu_time_used);

    // Free allocated memory
    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(C, N);

    return 0;
}