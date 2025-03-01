#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

long getCurrentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main() {
    const int MAXN = 10000000;
    bool *isPrime = (bool*)malloc(MAXN * sizeof(bool));
    if (!isPrime) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // init
    for (int i = 0; i < MAXN; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    if (MAXN > 1) {
        isPrime[1] = false;
    }

    long start = getCurrentTimeMillis();

    // Sieve
    for(int i = 2; i * i < MAXN; i++) {
        if(isPrime[i]) {
            for(int j = i * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }

    long end = getCurrentTimeMillis();
    printf("Sieve Time: %ld ms\n", (end - start));

    free(isPrime);
    return 0;
}
