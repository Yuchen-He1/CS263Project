#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// Bubble Sort function
void bubble_sort(vector<int>& arr) {
    int N = arr.size();
    for (int i = 0; i < N - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < N - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_bubble_sort(int N) {
        if (N <= 0) {
            return;  // Ignore invalid input
        }

        std::mt19937 rng(42);  // Fixed seed for reproducibility
        std::uniform_int_distribution<int> dist(0, 10000);

        vector<int> arr(N);
        for (int& num : arr) num = dist(rng);

        bubble_sort(arr);
    }
}
