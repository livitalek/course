#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Arguments error (less then 3)\n");
        exit(EXIT_FAILURE);
    }
    double result = 1;
    int i;
    for (i = 1; i < argc; i++) {
        result *= atof(argv[i]);
    }
    printf("Result: %.3f\n", result);
    exit(EXIT_SUCCESS);
}