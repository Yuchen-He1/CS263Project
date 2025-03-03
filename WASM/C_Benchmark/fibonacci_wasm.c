#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>  // Emscripten-specific functions

// Recursive Fibonacci function
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Ensure function is exported for WebAssembly
EMSCRIPTEN_KEEPALIVE
long long run_fibonacci(int n) {
    if (n < 0) {
        printf("Invalid Fibonacci number.\n");
        return -1;
    }
    return fibonacci(n);
}

// Main function (used for native execution)
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    long long result = run_fibonacci(n);
    printf("Fibonacci(%d) = %lld\n", n, result);
    return 0;
}
