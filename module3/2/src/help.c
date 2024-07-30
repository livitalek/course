#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char line1[200]="%s\nExample:\n>>%s <number1> <number2> .. <number49>\n";
    char line2[200]="%s\nExample:\n>>%s <number1> <number2>\n";

    if (argc == 1) {
        printf("More informaion\n");
        printf("All commands:\n");
        printf("* sum - summation\n");
        printf("* sub - subtraction\n");
        printf("* mul - multiplaction\n");
        printf("* div - division\n");
        printf("* max - maximum\n");
        printf("* min - minimum\n");
        printf("* help - help\n");
        printf("* exit - exit from terminal\n");
        printf("For more information about commnad, enter\n>>help <command>\n");
    } else {
        if (strcmp("sum", argv[1]) == 0) {
            printf(line1, "Summation all numbers.", argv[1]);
        } else if (strcmp("sub", argv[1]) == 0) {
            printf(line2, "Subtraction 2 numbers.", argv[1]);
        } else if (strcmp("mul", argv[1]) == 0) {
            printf(line1, "Multiplaction all numbers.", argv[1]);
        } else if (strcmp("div", argv[1]) == 0) {
            printf(line2, "Division 2 numbers.", argv[1]);
        } else if (strcmp("max", argv[1]) == 0) {
            printf(line1, "Finds the maximum number from the entire set.", argv[1]);
        } else if (strcmp("min", argv[1]) == 0) {
            printf(line1, "Finds the minimum number from the entire set.", argv[1]);
        } else if (strcmp("help", argv[1]) == 0) {
            printf("Show all commands.\nExample:\n>>help\n");
        } else if (strcmp("exit", argv[1]) == 0) {
            printf("Exit from terminal\nExample:\n>>exit\n");
        } else {
            printf("Don't understand command: %s\n", argv[1]);
        }
    }
}