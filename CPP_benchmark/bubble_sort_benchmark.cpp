#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

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

int main(int argc, char* argv[]) {
    std::mt19937 rng(42);  // Fixed seed for reproducibility
    std::uniform_int_distribution<int> dist(0, 10000);
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <array_size>" << endl;
        return 1;
    }

    int N = stoi(argv[1]);
    vector<int> arr(N);
    for (int& num : arr) num = rand();

    auto start = high_resolution_clock::now();
    bubble_sort(arr);
    auto end = high_resolution_clock::now();

    cout << "Bubble Sort | Array Size: " << N 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
