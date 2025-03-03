#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>  // Required for WebAssembly compatibility

// Simulate moving a disk (no actual output to avoid slowdowns)
void moveDisk(int n, char from, char to) {
    // Placeholder function to simulate move without affecting performance
}

// Recursive Tower of Hanoi function
void hanoi(int n, char from, char aux, char to) {
    if (n == 1) {
        moveDisk(n, from, to);
        return;
    }
    hanoi(n - 1, from, to, aux);
    moveDisk(n, from, to);
    hanoi(n - 1, aux, from, to);
}

// WebAssembly-compatible entry point
EMSCRIPTEN_KEEPALIVE
void run_hanoi(int n) {
    if (n < 1) {
        return;  // Ignore invalid input
    }
    hanoi(n, 'A', 'B', 'C');
}
