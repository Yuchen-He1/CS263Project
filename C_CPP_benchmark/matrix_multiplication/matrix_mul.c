#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>   // For times()
#include <sys/time.h>    // For gettimeofday()
#include <unistd.h>      // For sysconf()
 
// 获取当前墙钟时间（秒）
double get_wall_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;  // 单位：秒
}
 
int main(int argc, char *argv[]) {
    int N = 1000;
    struct tms start_cpu, end_cpu;
    clock_t start_time, end_time;
    long ticks_per_sec = sysconf(_SC_CLK_TCK);
 
    double start_wall_time = get_wall_time();
    start_time = times(&start_cpu);
 
    // init
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
 
    // mul
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
 
    end_time = times(&end_cpu);
    double end_wall_time = get_wall_time();
 
    // count
    double user_time   = (double)(end_cpu.tms_utime - start_cpu.tms_utime) / ticks_per_sec * 1000;
    double system_time = (double)(end_cpu.tms_stime - start_cpu.tms_stime) / ticks_per_sec * 1000;
    double elapsed_time = (end_wall_time - start_wall_time) * 1000;
 
    //printf("User CPU time: %.2f ms\n", user_time);
    //printf("System CPU time: %.2f ms\n", system_time);
    printf("Elapsed (wall-clock) Time: %.2f ms\n", elapsed_time);
 
    // release
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
