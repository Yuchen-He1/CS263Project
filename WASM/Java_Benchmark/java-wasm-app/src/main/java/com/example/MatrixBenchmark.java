package com.example;

import java.util.Random;

public class MatrixBenchmark {
    public static int[][] multiplyMatrices(int[][] A, int[][] B, int N) {
        int[][] C = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        Random rand = new Random(42);
        
        int[][] A = new int[N][N], B = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                A[i][j] = rand.nextInt(10000);
                B[i][j] = rand.nextInt(10000);
            }

        long start = System.nanoTime();
        int[][] C = multiplyMatrices(A, B, N);
        long end = System.nanoTime();

        System.out.printf("Matrix Multiplication | Size: %dx%d | Time: %.2f ms%n", N, N, (end - start) / 1e6);
    }
}
