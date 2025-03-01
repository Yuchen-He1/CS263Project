#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   // gettimeofday()
#include <sys/times.h>  // times()
#include <unistd.h>     // sysconf(), read(), write(), close()
#include <fcntl.h>      // open()
#include <time.h>
 
#define FILE_SIZE_MB 100
#define BUFFER_SIZE 4096  // 4KB
 

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
 

void test_file_io(const char *filename) {
    int fd;
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) 
        buffer[i] = 'A';
 

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file for writing");
        return;
    }
    for (int i = 0; i < (FILE_SIZE_MB * 1024 * 1024) / BUFFER_SIZE; i++) {
        if (write(fd, buffer, BUFFER_SIZE) < 0) {
            perror("Failed during write");
            close(fd);
            return;
        }
    }
    close(fd);
 

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file for reading");
        return;
    }
    while (read(fd, buffer, BUFFER_SIZE) > 0);
    close(fd);
 
 
    if (remove(filename) != 0) {
        perror("Failed to delete file");
    }
}
 
int main() {
    double start_wall, end_wall, start_cpu, end_cpu;
 
    start_wall = get_wall_time();
    start_cpu = get_cpu_time();
    test_file_io("testfile.txt");
    end_wall = get_wall_time();
    end_cpu = get_cpu_time();
 
    printf("File I/O - Wall Time: %.2f ms, CPU Time: %.2f ms\n", 
           (end_wall - start_wall) * 1000, (end_cpu - start_cpu) * 1000);
 
    return 0;
}
