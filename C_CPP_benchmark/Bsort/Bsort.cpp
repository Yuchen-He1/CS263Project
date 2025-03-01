#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

int main() {
    const int N = 1e5; 

    vector<int> arr(N);
    for(int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    auto start = chrono::high_resolution_clock::now();

    // Bubble Sort
    for(int i = 0; i < N - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < N - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if(!swapped) break;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Bubble Sort Time: " << duration << " ms" << endl;

    return 0;
}
