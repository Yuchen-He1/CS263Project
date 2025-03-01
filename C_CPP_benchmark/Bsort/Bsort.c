#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

long getCurrentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main() {
    int N = 100000;
    int *arr = (int*)malloc(N * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // init
    for(int i = 0; i < N; i++) {
        arr[i] = rand();
    }

    long start = getCurrentTimeMillis();

    // Bubble Sort
    for(int i = 0; i < N - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < N - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if(!swapped) break;
    }

    long end = getCurrentTimeMillis();
    printf("Bubble Sort Time: %ld ms\n", (end - start));

    free(arr);
    return 0;
}
