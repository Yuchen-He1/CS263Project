#include <stdio.h>
#include <string.h>

// Vulnerable function: directly uses user input as format string.
void vulnerable_printf(const char *user_input) {
    // This secret is stored on the stack.
    char secret[32] = "MY_SECRET_DATA";
    char dummy[16] = "DUMMY_DATA";  // extra variable to help demonstrate stack layout

    // Print a header message.
    printf("User supplied string: ");
    
    // Vulnerability: user_input is used directly as format string.
    printf(user_input);
    printf("\n");

    // Print the secret stored on the stack.
    printf("Secret stored on stack: %s\n", secret);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }
    vulnerable_printf(argv[1]);
    return 0;
}
