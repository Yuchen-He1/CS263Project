import java.util.Random;

public class BubbleSortBenchmark {

    public static long getCurrentTimeMillis() {
        return System.currentTimeMillis();
    }

    public static void main(String[] args) {
        int N = 100000;
        int[] arr = new int[N];

        // Initialize array with random numbers
        Random rand = new Random();
        for (int i = 0; i < N; i++) {
            arr[i] = rand.nextInt();
        }

        long start = getCurrentTimeMillis();

        // Bubble Sort
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

        long end = getCurrentTimeMillis();
        System.out.println("Bubble Sort Time: " + (end - start) + " ms");
    }
}
