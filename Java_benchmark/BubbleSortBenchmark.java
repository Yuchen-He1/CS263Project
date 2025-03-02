import java.util.Random;

public class BubbleSortBenchmark {
    public static void bubbleSort(int[] arr) {
        int N = arr.length;
        for (int i = 0; i < N - 1; i++) {
            boolean swapped = false;
            for (int j = 0; j < N - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int[] arr = new Random(42).ints(N, 0, 10000).toArray();

        long start = System.nanoTime();
        bubbleSort(arr);
        long end = System.nanoTime();

        System.out.printf("Bubble Sort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
    }
}
