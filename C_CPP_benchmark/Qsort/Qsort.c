#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long getCurrentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void quicksort(int *arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        if (i < j) arr[i++] = arr[j];
        while (i < j && arr[i] <= pivot) i++;
        if (i < j) arr[j--] = arr[i];
    }
    arr[i] = pivot;
    quicksort(arr, left, i - 1);
    quicksort(arr, i + 1, right);
}

int main() {
    const int N = 200000;
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
    quicksort(arr, 0, N - 1);
    long end = getCurrentTimeMillis();

    printf("Quick Sort Time: %ld ms\n", (end - start));

    free(arr);
    return 0;
}
