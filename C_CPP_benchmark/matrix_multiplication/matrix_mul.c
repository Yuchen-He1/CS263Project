// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// void printMatrix(int **matrix, int N) {
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             printf("%d\t", matrix[i][j]);
//         }
//         printf("\n");
//     }
// }

// // Function to free allocated memory
// void freeMatrix(int **matrix, int N) {
//     for (int i = 0; i < N; i++) {
//         free(matrix[i]);
//     }
//     free(matrix);
// }

// int main(int argc, char *argv[]) {
//     int N = atoi(argv[1]);

//     // Allocate memory for matrices
//     int **A = (int **)malloc(N * sizeof(int *));
//     int **B = (int **)malloc(N * sizeof(int *));
//     int **C = (int **)malloc(N * sizeof(int *));
    
//     for (int i = 0; i < N; i++) {
//         A[i] = (int *)malloc(N * sizeof(int));
//         B[i] = (int *)malloc(N * sizeof(int));
//         C[i] = (int *)malloc(N * sizeof(int));
        
//         // Check if memory allocation was successful
//         if (A[i] == NULL || B[i] == NULL || C[i] == NULL) {
//             printf("Memory allocation failed!\n");
//             return 1;
//         }
//     }

//     // Initialize matrices A and B with random values
//     srand(time(NULL));  // Initialize random seed
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             A[i][j] = rand() % 10;  // Random values between 0-9
//             B[i][j] = rand() % 10;
//         }
//     }

//     //printf("\nMatrix A:\n");
//     //printMatrix(A, N);
//     //printf("\nMatrix B:\n");
//     //printMatrix(B, N);

//     // Start timing
//     clock_t start = clock();

//     // Perform matrix multiplication
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             C[i][j] = 0;
//             for (int k = 0; k < N; k++) {
//                 C[i][j] += A[i][k] * B[k][j];
//             }
//         }
//     }

//     // End timing
//     clock_t end = clock();
//     double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

//     //printf("\nResultant Matrix C:\n");
//     //printMatrix(C, N);
//     //printf("\nExecution time: %f seconds\n", cpu_time_used);

//     // Free allocated memory
//     freeMatrix(A, N);
//     freeMatrix(B, N);
//     freeMatrix(C, N);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>   // For times()
#include <sys/time.h>    // For gettimeofday()
#include <unistd.h>      // For sysconf()

// Function to get current wall-clock time in seconds
double get_wall_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;  // Convert to seconds
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    struct tms start_cpu, end_cpu;
    clock_t start_time, end_time;
    long ticks_per_sec = sysconf(_SC_CLK_TCK);  // Get clock ticks per second

    double start_wall_time = get_wall_time();  // Start wall-clock time
    start_time = times(&start_cpu);  // Start CPU time tracking

    // Perform matrix multiplication (workload)
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
        
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End timing
    end_time = times(&end_cpu);  // End CPU time tracking
    double end_wall_time = get_wall_time();  // End wall-clock time

    // Compute CPU times
    double user_time = (double)(end_cpu.tms_utime - start_cpu.tms_utime) / ticks_per_sec;
    double system_time = (double)(end_cpu.tms_stime - start_cpu.tms_stime) / ticks_per_sec;
    double elapsed_time = end_wall_time - start_wall_time;

    // Print results
    printf("User CPU time: %.6f seconds\n", user_time);
    printf("System CPU time: %.6f seconds\n", system_time);
    printf("Elapsed (wall-clock) time: %.6f seconds\n", elapsed_time);

    // Free memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
