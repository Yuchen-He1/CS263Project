#include <iostream>
#include <fstream>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>    // for remove()

using namespace std;

static const int FILE_SIZE_MB = 100;
static const int BUFFER_SIZE  = 4096;

void test_file_io(const char *filename) {
    // 初始化缓冲区
    char buffer[BUFFER_SIZE];
    memset(buffer, 'A', BUFFER_SIZE);

    // 写文件
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0) {
        cerr << "Failed to open file for writing.\n";
        return;
    }
    long totalWrites = (FILE_SIZE_MB * 1024LL * 1024LL) / BUFFER_SIZE;
    for(long i = 0; i < totalWrites; i++) {
        if(write(fd, buffer, BUFFER_SIZE) < 0) {
            cerr << "Write error\n";
            close(fd);
            return;
        }
    }
    close(fd);

    // 读文件
    fd = open(filename, O_RDONLY);
    if(fd < 0) {
        cerr << "Failed to open file for reading.\n";
        return;
    }
    while(read(fd, buffer, BUFFER_SIZE) > 0) { /* do nothing */ }
    close(fd);

    // 删除文件
    if(remove(filename) != 0) {
        cerr << "Failed to delete file: " << filename << "\n";
    }
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    test_file_io("testfile.txt");
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "File I/O - Wall Time: " << duration << "ms" << endl;

    return 0;
}
