#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday()
#include <sys/times.h>  // times()
#include <unistd.h>

// 获取当前墙钟时间（秒）
double get_wall_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

// 获取当前 CPU 时间（秒）
double get_cpu_time() {
    struct tms time_sample;
    clock_t clock_time = times(&time_sample);
    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    return (double)clock_time / ticks_per_sec;
}

// 递归计算斐波那契数列
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <fibonacci_n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // 获取斐波那契数的 N 值
    double start_wall, end_wall, start_cpu, end_cpu;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    long long result = fibonacci(n);
    end_wall = get_wall_time();
    end_cpu = get_cpu_time();

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Recursion - Wall Time: %.6f s, CPU Time: %.6f s\n", end_wall - start_wall, end_cpu - start_cpu);

    return 0;
}
