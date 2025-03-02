#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    auto start = high_resolution_clock::now();
    long long result = fibonacci(n);
    auto end = high_resolution_clock::now();

    cout << "Fibonacci | N: " << n 
         << " | Result: " << result 
         << " | Time: " << duration<double, milli>(end - start).count() << " ms" << endl;
    return 0;
}
