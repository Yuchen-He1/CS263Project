#include <stdio.h>

int main(void) {
    int *p = NULL; // p is a NULL pointer
    // Dereferencing a NULL pointer causes undefined behavior, typically a segmentation fault.
    printf("Value at p: %d\n", *p);
    return 0;
}
