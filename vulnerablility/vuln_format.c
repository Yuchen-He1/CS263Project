#include <stdio.h>

// A function with a format string vulnerability
void vulnerable_printf(const char *user_input) {
    // Directly using user input as the format string instead of a fixed format
    printf(user_input);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <format_string>\n", argv[0]);
        return 1;
    }
    vulnerable_printf(argv[1]);
    return 0;
}
