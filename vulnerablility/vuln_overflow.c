#include <stdio.h>
#include <string.h>

// A function with a buffer overflow vulnerability
void vulnerable_function(const char *input) {
    char buffer[32];
    // No length check on input – leads to potential buffer overflow
    strcpy(buffer, input);
    printf("Buffer true length: %lu\n", sizeof(buffer));
    printf("Buffer length: %lu\n", strlen(buffer));
    printf("Buffer content: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }
    vulnerable_function(argv[1]);
    return 0;
}
