import time

def prime_sieve(N):
    prime = [True] * (N + 1)
    prime[0] = prime[1] = False

    for p in range(2, int(N**0.5) + 1):
        if prime[p]:
            for i in range(p * p, N + 1, p):
                prime[i] = False

    return prime

def main():
    N = int(input("Enter upper limit for prime sieve: "))

    start_time = time.perf_counter()
    primes = prime_sieve(N)
    end_time = time.perf_counter()

    print(f"Prime Sieve | Upper Limit: {N} | Time: {(end_time - start_time) * 1000:.2f} ms")

if __name__ == "__main__":
    main()
