#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    //char buffer[32];
    void (*func_ptr)();
} Data;

Data *globalData = NULL;
void legit_function() {
    printf("Legit function\n");
}
void malicious_function() {
    printf("Malicious function\n");
}
void allocateData() {
    globalData = (Data *) malloc(sizeof(Data));
    if (!globalData) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    globalData->func_ptr = legit_function;
    printf("legit function pointer %p\n", globalData->func_ptr);
    globalData->func_ptr();
    // Initialize the buffer with sensitive information.
    //strcpy(globalData->buffer, "SensitiveInformation");
}

void freeData() {
    free(globalData);
    // Now, globalData becomes a dangling pointer.
}

void useData(const char *userInput) {
    // Vulnerable: Using globalData after it has been freed.
    // This may leak or corrupt sensitive information.
    printf("Pointer value after free %p\n", globalData);
    //printf("Leaked Data (from freed memory): %s\n", globalData->buffer);
    //printf("Leaked Data : %s\n", globalData);
    printf("allocate a new memory\n");
    Data *newData = (Data *) malloc(sizeof(Data));
    newData->func_ptr = malicious_function;
    //may excute malicious function
    globalData->func_ptr();
    printf("malicious function pointer %p\n", globalData->func_ptr);
    //if (strcmp(userInput, globalData->buffer) == 0) {
        //printf("Access granted!\n");
    //} else {
        //printf("Access denied!\n");
    //}
}

int main(int argc, char *argv[]) {

    allocateData();
    printf("Pointer value after allocation %p\n", globalData);
    //printf("Data: %s\n", globalData->buffer);
    freeData();
    useData(argv[1]);
    return 0;
}