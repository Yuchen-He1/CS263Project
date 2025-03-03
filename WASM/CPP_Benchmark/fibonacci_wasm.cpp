#include <iostream>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// Recursive Fibonacci function
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    long long run_fibonacci(int n) {
        if (n < 0) {
            return -1;  // Ignore invalid input
        }
        return fibonacci(n);
    }
}
