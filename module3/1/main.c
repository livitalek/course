#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Index{
    int pos;
    double value;
} Index;

double square(double a);
void print(Index a);

int main(int argc, char* argv[]) {
    int i, n = argc - 1;
    
    Index mas[n];
    printf("Arguments:\n");
    for (i = 1; i < argc; i++) {
        mas[i - 1].pos = i - 1;
        mas[i - 1].value = atof(argv[i]);
        print(mas[i - 1]);
    }
    printf("\n\nResults:\n");

    int n1 = n / 2 + ((n % 2 == 1) ? 1 : 0) , n2 = n / 2;
    Index parent[n1], child[n2];
    int j, k;
    for (i = 0, j = 0, k = 0; i < n; i++) {
        if (i % 2 == 0) {
            parent[j++] = mas[i];
        } else {
            child[k++] = mas[i];
        }
    }


    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("I'm child process PID: %d\n", getpid());
        for (i = 0; i < n2; i++) {
            child[i].value = square(child[i].value);
            print(child[i]);
        }
        exit(EXIT_SUCCESS);
    } else {
        printf("I'm parent process PID: %d, my child process PID: %d\n", getpid(), pid);
        for (i = 0; i < n1; i++) {
            parent[i].value = square(parent[i].value);
            print(parent[i]);
        }
        wait();
        printf("Child process complete\n");
        exit(EXIT_SUCCESS);
    }
}

double square(double a) {
    return a * a;
}

void print(Index a) {
    printf("mas[%d] = %.3f;\n", a.pos, a.value);
}