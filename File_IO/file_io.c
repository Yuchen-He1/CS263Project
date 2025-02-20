#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday() - 计算墙钟时间
#include <sys/times.h>  // times() - 计算CPU时间
#include <unistd.h>     // sysconf(), read(), write(), close()
#include <fcntl.h>      // open()
#include <time.h>

#define FILE_SIZE_MB 100
#define BUFFER_SIZE 4096  // 4KB

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
    /*Cpu time is incorrect in wasm.This happens 
    because:WebAssembly (WASI) does not support times() properly.
    sysconf(_SC_CLK_TCK) returns a bad value in WASM.*/
    return (double)clock_time / ticks_per_sec;
}

// 测试文件 I/O（写入 100MB 数据，然后读取）
void test_file_io(const char *filename) {
    int fd;
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) buffer[i] = 'A';  // 填充缓冲区

    // 开始写入
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file for writing");
        return;
    }
    for (int i = 0; i < (FILE_SIZE_MB * 1024 * 1024) / BUFFER_SIZE; i++) {
        write(fd, buffer, BUFFER_SIZE);
    }
    close(fd);

    // 开始读取
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file for reading");
        return;
    }
    while (read(fd, buffer, BUFFER_SIZE) > 0);
    close(fd);
}

int main() {
    double start_wall, end_wall, start_cpu, end_cpu;

    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    test_file_io("testfile.txt");
    end_wall = get_wall_time();
    end_cpu = get_cpu_time();

    printf("File I/O - Wall Time: %.6f s, CPU Time: %.6f s\n", end_wall - start_wall, end_cpu - start_cpu);

    return 0;
}
