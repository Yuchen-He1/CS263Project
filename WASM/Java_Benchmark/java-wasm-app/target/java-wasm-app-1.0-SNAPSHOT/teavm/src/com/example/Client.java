package com.example;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import org.teavm.jso.dom.html.HTMLDocument;

public class Client {
    public static void main(String[] args) {
       
        var document = HTMLDocument.current();
        var div = document.createElement("div");

        String outputStr = "Language,Benchmark,Input Size,Time (ms)";

        div.appendChild(document.createTextNode(outputStr));
        

        var br = document.createElement("br");
        div.appendChild(br);


        String[] keys = new String[]{"Bubble Sort", "Fibonacchi", "Tower of Hanoi", "Matrix Multiplication", "Quick Sort", "Prime Number"};
        
        Map<String, Integer[]> map = new HashMap<>();
        map.put(keys[0], new Integer[]{1000, 5000, 10000, 50000});
        map.put(keys[1], new Integer[]{30, 32, 34, 36, 38, 40});
        map.put(keys[2], new Integer[]{10, 15, 20, 22, 24, 25});
        map.put(keys[3], new Integer[]{100, 200, 300, 400, 500});
        map.put(keys[4], new Integer[]{1000, 5000, 10000, 50000, 100000});
        map.put(keys[5], new Integer[]{100000, 500000, 1000000, 5000000});
        

        for (Map.Entry<String, Integer[]> entry : map.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue());
            if(entry.getKey()==keys[0]) {
                for(int N: entry.getValue()){
                    // int N = 100000;
                    int[] arr = new Random(42).ints(N, 0, 10000).toArray();
                    long start = System.nanoTime();
                    BubbleSortBenchmark.bubbleSort(arr);
                    long end = System.nanoTime();
                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }

            if(entry.getKey()==keys[1]) {
                for(int N: entry.getValue()){
                    // int N = 100000;
                    // int[] arr = new Random(42).ints(N, 0, 10000).toArray();
                    long start = System.nanoTime();
                    FibonacciBenchmark.fibonacci(N);
                    long end = System.nanoTime();
                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }

            if(entry.getKey()==keys[2]) {
                for(int N: entry.getValue()){
                    // int N = 100000;
                    int[] arr = new Random(42).ints(N, 0, 10000).toArray();
                    long start = System.nanoTime();
                    HanoiBenchmark.hanoi(N, 'A', 'B', 'C');
                    long end = System.nanoTime();
                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }

            if(entry.getKey()==keys[3]) {
                for(int N: entry.getValue()){
                    
                    Random rand = new Random(42);
                    
                    int[][] A = new int[N][N], B = new int[N][N];
                    for (int i = 0; i < N; i++)
                        for (int j = 0; j < N; j++) {
                            A[i][j] = rand.nextInt(10000);
                            B[i][j] = rand.nextInt(10000);
                        }

                    long start = System.nanoTime();
                    int[][] C = MatrixBenchmark.multiplyMatrices(A, B, N);
                    long end = System.nanoTime();
                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }

            if(entry.getKey()==keys[4]) {
                for(int N: entry.getValue()){
                    int[] arr = new Random(42).ints(N, 0, 10000).toArray();

                    long start = System.nanoTime();
                    Arrays.sort(arr);  // Java's built-in QuickSort
                    long end = System.nanoTime();
                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }

            if(entry.getKey()==keys[5]) {
                for(int N: entry.getValue()){
                   
                    long start = System.nanoTime();
                    boolean[] primes = PrimeSieveBenchmark.primeSieve(N);
                    long end = System.nanoTime();

                    double diff = (end-start)/1e6;
                    String str = "Java,"+entry.getKey()+","+N+","+diff;
                    div.appendChild(document.createTextNode(str));
                    div.appendChild(br);
                }
            }
        }

        // int N = 100000;
        // int[] arr = new Random(42).ints(N, 0, 10000).toArray();

        // long start = System.nanoTime();
        // BubbleSortBenchmark.bubbleSort(arr);
        // long end = System.nanoTime();

        // System.out.printf("Bubble Sort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
        
        // String str = String.format("Bubble Sort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
        // div.appendChild(document.createTextNode(str));

        // double diff = (end-start)/1e6;
        // var document = HTMLDocument.current();
        // var div = document.createElement("div");

        // String outputStr = "Language,Benchmark,Input Size,Time (ms) \n";

        // div.appendChild(document.createTextNode(outputStr));
        

        // var br = document.createElement("br");
        // div.appendChild(br);
        // div.appendChild(document.createTextNode(outputStr + "Benchmark: Bubble Sort, N = " + N + ", Time = " + diff + "ms"));        
        document.getBody().appendChild(div);


    }
}
