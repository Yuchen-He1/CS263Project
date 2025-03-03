#include <iostream>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// Recursive Tower of Hanoi function
void hanoi(int n, char from, char aux, char to) {
    if (n == 1) return;
    hanoi(n - 1, from, to, aux);
    hanoi(n - 1, aux, from, to);
}

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_hanoi(int n) {
        if (n < 1) {
            return;  // Ignore invalid input
        }
        hanoi(n, 'A', 'B', 'C');
    }
}
