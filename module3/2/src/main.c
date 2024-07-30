#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 100

int main(int argc, char* argv[]) {
    printf("Welcom to my terminal\n");
    printf("Enter your command\n");
    printf("For help print: >>help\n");
    char line[5400];
    char curs[5398];
    char *args[MAX_ARGS];
    char *token;
    int i;

    while(1) {

        do {
            printf(">>");
            if (fgets(curs, sizeof(curs), stdin) != NULL) {
                curs[strcspn(curs, "\n")] = 0;
            }
        } while (strlen(curs) == 0);

        sprintf(line, "./%s", curs);

        token = strtok(line, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++]=token;

            token=strtok(NULL, " ");
        }

        args[i] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (strcmp("./exit", args[0]) == 0) {
                exit(EXIT_FAILURE);                
            } 
            
            execvp(args[0], args);
            
            exit(EXIT_SUCCESS);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (strcmp("./exit", args[0]) == 0) {
                exit(EXIT_SUCCESS);
            }
        }
    }

    exit(EXIT_SUCCESS);
}

/*
void use_help() {
    printf("All commands:");
    printf("sum, sub, mul, div, pow, max, min: math commands\n");
    printf("arg: save argumets. maximum 100 elements\n");
    printf("print: print arguments\n");
    printf("help: show information for help\n");
    printf("history: show all history\n");
    printf("exit: exit from terminal\n");
    printf("for more information print >>help <command>\n");
    return;
}*/
 