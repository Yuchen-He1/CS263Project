package com.example;

public class HanoiBenchmark {
    public static void hanoi(int n, char from, char aux, char to) {
        if (n == 1) return;
        hanoi(n - 1, from, to, aux);
        hanoi(n - 1, aux, from, to);
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);

        long start = System.nanoTime();
        hanoi(N, 'A', 'B', 'C');
        long end = System.nanoTime();

        System.out.printf("Hanoi | Disks: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
    }
}
