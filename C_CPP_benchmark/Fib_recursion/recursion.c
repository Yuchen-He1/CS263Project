#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday()
#include <sys/times.h>  // times()
#include <unistd.h>

double get_wall_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

double get_cpu_time() {
    struct tms time_sample;
    clock_t clock_time = times(&time_sample);
    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    return (double)clock_time / ticks_per_sec;
}

long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int n = 40;
    double start_wall, end_wall, start_cpu, end_cpu;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    long long result = fibonacci(n);
    end_wall = get_wall_time();
    end_cpu = get_cpu_time();

    // 将时间乘以 1000 转换为毫秒输出
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Recursion - Wall Time: %.2f ms, CPU Time: %.2f ms\n",
           (end_wall - start_wall) * 1000,
           (end_cpu - start_cpu) * 1000);

    return 0;
}
