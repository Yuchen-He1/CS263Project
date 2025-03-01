#include <stdio.h>
#include <sys/time.h>

long getCurrentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void moveDisk(int n, char from, char to) {
    // print procedure
    // printf("Move disk %d from %c to %c\n", n, from, to);
}

void hanoi(int n, char from, char aux, char to) {
    if(n == 1) {
        moveDisk(n, from, to);
        return;
    }
    hanoi(n - 1, from, to, aux);
    moveDisk(n, from, to);
    hanoi(n - 1, aux, from, to);
}

int main() {
    int n = 25;
    long start = getCurrentTimeMillis();
    hanoi(n, 'A', 'B', 'C');
    long end = getCurrentTimeMillis();
    printf("Hanoi Time: %ld ms\n", (end - start));
    return 0;
}
