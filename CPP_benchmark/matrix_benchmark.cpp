#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<vector<int>> multiply_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int N) {
    vector<vector<int>> C(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main(int argc, char* argv[]) {
    std::mt19937 rng(42);  // Fixed seed for reproducibility
    std::uniform_int_distribution<int> dist(0, 10000);
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <matrix_size>" << endl;
        return 1;
    }

    int N = stoi(argv[1]);
    vector<vector<int>> A(N, vector<int>(N, rand() % 10));
    vector<vector<int>> B(N, vector<int>(N, rand() % 10));

    auto start = high_resolution_clock::now();
    vector<vector<int>> C = multiply_matrices(A, B, N);
    auto end = high_resolution_clock::now();

    cout << "Matrix Multiplication | Size: " << N 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
