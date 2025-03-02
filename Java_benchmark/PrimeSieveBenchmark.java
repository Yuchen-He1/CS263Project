public class PrimeSieveBenchmark {
    public static boolean[] primeSieve(int N) {
        boolean[] prime = new boolean[N + 1];
        for (int i = 2; i <= N; i++) prime[i] = true;

        for (int p = 2; p * p <= N; p++)
            if (prime[p])
                for (int i = p * p; i <= N; i += p)
                    prime[i] = false;

        return prime;
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);

        long start = System.nanoTime();
        boolean[] primes = primeSieve(N);
        long end = System.nanoTime();

        System.out.printf("Prime Sieve | Upper Limit: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
    }
}
