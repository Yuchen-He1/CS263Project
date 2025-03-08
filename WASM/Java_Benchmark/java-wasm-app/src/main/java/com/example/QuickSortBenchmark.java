package com.example;

import java.util.Arrays;
import java.util.Random;

public class QuickSortBenchmark {
    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int[] arr = new Random(42).ints(N, 0, 10000).toArray();

        long start = System.nanoTime();
        Arrays.sort(arr);  // Java's built-in QuickSort
        long end = System.nanoTime();

        System.out.printf("QuickSort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
    }
}
