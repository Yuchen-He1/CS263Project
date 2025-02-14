public class Main {

    public static void main(String args[]) {
        long startTime = System.nanoTime();
        testFunction();
        long endTime = System.nanoTime();
        System.out.println("Execution Time: " + (double)(endTime - startTime)/1000000 + " ms");
    }

    public static void testFunction() {
        System.out.println("Hello world from Java");
    }

}