#include <iostream>
#include <vector>
#include <emscripten.h>  // Required for WebAssembly compatibility

using namespace std;

// Prime number sieve function
void prime_sieve(int N, vector<bool>& prime) {
    fill(prime.begin(), prime.end(), true);
    prime[0] = prime[1] = false;
    for (int p = 2; p * p <= N; p++)
        if (prime[p])
            for (int i = p * p; i <= N; i += p)
                prime[i] = false;
}

// WebAssembly-compatible entry point
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_prime_sieve(int N) {
        if (N <= 1) {
            return;  // Ignore invalid input
        }
        vector<bool> prime(N + 1);
        prime_sieve(N, prime);
    }
}
