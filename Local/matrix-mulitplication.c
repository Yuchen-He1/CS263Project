#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/resource.h>

void print_matrix(int **matrix, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **multiply(int **matrixA, int **matrixB, int rowA, int colA, int colB)
{
    int **result = (int **)malloc(rowA * sizeof(int *));
    int i, j, k;

    for (i = 0; i < rowA; i++)
    {
        result[i] = (int *)malloc(colA * sizeof(int));
    }

    for (i = 0; i < rowA; i++)
    {
        for (j = 0; j < colB; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < colA; k++)
            {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // print_matrix(result, rowA, colB);
    return result;
}

int **get_random_matrix(int row, int col)
{
    int **matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        matrix[i] = (int *)malloc(col * sizeof(int));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }

    return matrix;
}

void run_matrix_multiplication()
{
    int rowA = 1000, colA = 2000, rowB = 2000, colB = 1000;
    int **matrixA = get_random_matrix(rowA, colA);
    int **matrixB = get_random_matrix(rowB, colB);
    int **result = multiply(matrixA, matrixB, rowA, colA, colB);
    print_matrix(result, rowA, colB);
}
// int main()
// {

//     // struct tms start, end;
//     // clock_t real_start = times(&start); // Start CPU time

//     // int rowA = 1000, colA = 2000, rowB = 2000, colB = 1000;
//     // int **matrixA = get_random_matrix(rowA, colA);
//     // int **matrixB = get_random_matrix(rowB, colB);
//     // int **result = multiply(matrixA, matrixB, rowA, colA, colB);
//     // print_matrix(result, rowA, colB);
//     // clock_t real_end = times(&end); // End CPU time

//     // long ticks_per_sec = sysconf(_SC_CLK_TCK);
//     // double user_time = (double)(end.tms_utime - start.tms_utime) / ticks_per_sec;
//     // double system_time = (double)(end.tms_stime - start.tms_stime) / ticks_per_sec;

//     // printf("User CPU time: %.6f seconds\n", user_time);
//     // printf("System CPU time: %.6f seconds\n", system_time);

//     // struct rusage usage;
//     // getrusage(RUSAGE_SELF, &usage);
//     // printf("Memory usage: %ld KB\n", usage.ru_maxrss);

//     // return 0;

//     int rowA = 1000, colA = 2000, rowB = 2000, colB = 1000;
//     int **matrixA = get_random_matrix(rowA, colA);
//     int **matrixB = get_random_matrix(rowB, colB);
//     int **result = multiply(matrixA, matrixB, rowA, colA, colB);
//     print_matrix(result, rowA, colB);

//     return 0;

//     // for(int r=2; r<40; r++){
//     //     int rowA, colA, rowB, colB;
//     //     int** matrixA;
//     //     if(r==2){
//     //         rowA = r-1;
//     //         colA = r;
//     //         rowB = r;
//     //         colB = r+1;
//     //     } else {
//     //         rowB = r;
//     //         colB = r+1;
//     //     }
//     //         matrixA= get_random_matrix(rowA, colA);
//     //     int** matrixB = get_random_matrix(rowB, colB);
//     //     printf("(%d,%d)(%d, %d)\n", rowA, colA, rowB, colB);
//     //     // print_matrix(matrixB);
//     //     int** result = multiply(matrixA, matrixB, rowA, colA, colB);
//     //     print_matrix(result, rowA, colB);
//     //     printf("*********");
//     //     matrixA = result;
//     //     rowA = rowA;
//     //     colA = colB;

//     // }

//     return 0;
// }