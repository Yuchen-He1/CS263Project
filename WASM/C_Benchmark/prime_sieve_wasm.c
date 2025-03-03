#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <emscripten.h>  // Required for WebAssembly compatibility

// Prime number sieve function
void prime_sieve(int N, bool *prime) {
    for (int i = 0; i <= N; i++) {
        prime[i] = true;
    }
    prime[0] = prime[1] = false;

    for (int p = 2; p * p <= N; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= N; i += p) {
                prime[i] = false;
            }
        }
    }
}

// WebAssembly-compatible entry point
EMSCRIPTEN_KEEPALIVE
void run_prime_sieve(int N) {
    if (N <= 1) {
        return;  // Ignore invalid input
    }

    // Allocate memory for prime number array
    bool *prime = (bool*)malloc((N + 1) * sizeof(bool));
    if (!prime) {
        return;  // Memory allocation failed
    }

    // Run the prime number sieve
    prime_sieve(N, prime);

    // Free allocated memory
    free(prime);
}
