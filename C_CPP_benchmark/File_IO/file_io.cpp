#include <iostream>
#include <fstream>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

using namespace std;

static const int FILE_SIZE_MB = 100;
static const int BUFFER_SIZE  = 4096;

void test_file_io(const char *filename) {
    // 初始化缓冲区
    char buffer[BUFFER_SIZE];
    memset(buffer, 'A', BUFFER_SIZE);

    // 打开文件 (不创建，仅写入)
    int fd = open(filename, O_WRONLY);
    if(fd < 0) {
        cerr << "Failed to open existing file for writing.\n";
        return;
    }

    // 计算总写入次数
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

    // 清空文件内容但不删除文件
    fd = open(filename, O_WRONLY | O_TRUNC);
    if (fd < 0) {
        cerr << "Failed to truncate file: " << filename << "\n";
        return;
    }
    close(fd);

    cout << "File content cleared but file is not deleted.\n";
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    test_file_io("testfile.txt");
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "File I/O - Wall Time: " << duration << "ms" << endl;

    return 0;
}
