def prime_sieve(N):
    prime = [True] * (N + 1)
    prime[0] = prime[1] = False

    for p in range(2, int(N**0.5) + 1):
        if prime[p]:
            for i in range(p * p, N + 1, p):
                prime[i] = False

    return prime

def run_prime_sieve(N):
    return prime_sieve(N)  # Returning the prime list for WebAssembly
