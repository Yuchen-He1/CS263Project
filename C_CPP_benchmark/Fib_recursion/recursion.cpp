#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

long long fibonacci(int n) {
    if(n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    //int n = atoi(argv[1]);
    int n = 40;
    auto start = chrono::high_resolution_clock::now();
    long long result = fibonacci(n);
    auto end = chrono::high_resolution_clock::now();

    cout << "Fibonacci(" << n << ") = " << result << endl;
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Recursion Time: " << ms << " ms" << endl;
    return 0;
}
