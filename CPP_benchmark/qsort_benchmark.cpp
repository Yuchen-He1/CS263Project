#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <array_size>" << endl;
        return 1;
    }

    int N = stoi(argv[1]);
    vector<int> arr(N);
    for (int& num : arr) num = rand();

    auto start = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    auto end = high_resolution_clock::now();

    cout << "QuickSort | Array Size: " << N 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
