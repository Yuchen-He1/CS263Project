#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
 
int main(int argc, char *argv[]) {
    int N = 1000;
    if (argc > 1) {
        N = atoi(argv[1]);
    }
 
    
    int **A = new int*[N];
    int **B = new int*[N];
    int **C = new int*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
        B[i] = new int[N];
        C[i] = new int[N];
    }
 
    // init
    srand(12345);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
 
    // count
    auto start = chrono::high_resolution_clock::now();
 
    // mul
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
 
    // count end 
    auto end = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double>(end - start).count() * 1000; // 转换为毫秒
 
    cout << "Matrix multiplication (" << N << "x" << N << ") done.\n";
    cout << "Elapsed time: " << elapsed << " ms" << endl;
 
    // free
    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
 
    return 0;
}
