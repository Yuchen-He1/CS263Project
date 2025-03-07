package com.example;

import java.util.Random;

import org.teavm.jso.dom.html.HTMLDocument;

public class Client {
    public static void main(String[] args) {
       
        int N = 100000;
        int[] arr = new Random(42).ints(N, 0, 10000).toArray();

        long start = System.nanoTime();
        BubbleSortBenchmark.bubbleSort(arr);
        long end = System.nanoTime();

        // System.out.printf("Bubble Sort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
        
        // String str = String.format("Bubble Sort | Array Size: %d | Time: %.2f ms%n", N, (end - start) / 1e6);
        // div.appendChild(document.createTextNode(str));

        double diff = (end-start)/1e6;
        var document = HTMLDocument.current();
        var div = document.createElement("div");

        String outputStr = "Language,Benchmark,Input Size,Time (ms) \n";


        div.appendChild(document.createTextNode(outputStr + "Benchmark: Bubble Sort, N = " + N + ", Time = " + diff + "ms"));        
        document.getBody().appendChild(div);


    }
}
