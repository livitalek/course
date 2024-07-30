#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Arguments error (less then 3)\n");
        exit(EXIT_FAILURE);
    }
    double result = 0, buf;
    result = atof(argv[1]);
    int i;
    for (i = 2; i < argc; i++) {
        if (result < (buf = atof(argv[i]))) {
            result = buf;
        }
    }
    printf("Result: %.3f\n", result);
    exit(EXIT_SUCCESS);
}