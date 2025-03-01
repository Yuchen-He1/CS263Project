#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

void quicksort(vector<int> &arr, int left, int right) {
    if(left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while(i < j) {
        while(i < j && arr[j] >= pivot) j--;
        if(i < j) arr[i++] = arr[j];
        while(i < j && arr[i] <= pivot) i++;
        if(i < j) arr[j--] = arr[i];
    }
    arr[i] = pivot;
    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}

int main() {
    const int N = 200000; 
    vector<int> arr(N);
    for(int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    auto start = chrono::high_resolution_clock::now();

    quicksort(arr, 0, N - 1);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Quick Sort Time: " << duration << " ms" << endl;

    return 0;
}
