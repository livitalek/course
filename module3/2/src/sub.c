#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Arguments error (not equal 3)\n");
        exit(EXIT_FAILURE);
    }
    printf("Result: %.3f\n", (double) atof(argv[1]) - atof(argv[2]));
    exit(EXIT_SUCCESS);
}