public class FibonacciBenchmark {
    public static long fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);

        long start = System.nanoTime();
        long result = fibonacci(N);
        long end = System.nanoTime();

        System.out.printf("Fibonacci | N: %d | Result: %d | Time: %.2f ms%n", N, result, (end - start) / 1e6);
    }
}
