#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// Function to multiply two matrices
vector<vector<int>> multiply_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int N) {
    vector<vector<int>> C(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_matrix_multiplication(int N) {
        if (N <= 0) {
            return;  // Ignore invalid input
        }

        std::mt19937 rng(42);  // Fixed seed for reproducibility
        std::uniform_int_distribution<int> dist(0, 10000);

        vector<vector<int>> A(N, vector<int>(N, dist(rng)));
        vector<vector<int>> B(N, vector<int>(N, dist(rng)));

        // Perform matrix multiplication
        vector<vector<int>> C = multiply_matrices(A, B, N);
    }
}
