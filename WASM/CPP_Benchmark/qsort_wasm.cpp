#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_qsort(int N) {
        if (N <= 0) {
            return;  // Ignore invalid input
        }

        std::mt19937 rng(42);  // Fixed seed for reproducibility
        std::uniform_int_distribution<int> dist(0, 10000);

        vector<int> arr(N);
        for (int& num : arr) num = dist(rng);

        // Perform QuickSort (std::sort)
        sort(arr.begin(), arr.end());
    }
}
