#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caluclator.h"

void info();

int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp("--help", argv[1]) == 0 || 
        strcmp("-h", argv[1]) == 0)) {
        info();
        return 0;
    } else if (argc < 4) {
        printf("Error: arguments less then 4.\n");
        printf("Show more information: ./main -h or ./main --help\n");
        return -1;
    }

    Operator result;

    if (strcmp(argv[1], "+") == 0 || strcmp(argv[1], "sum") == 0) {
        switch (argc)
        {
        case 4:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]));
            break;
        case 5:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]));
            break;
        case 6:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
            break;
        case 7:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
            break;
        case 8:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
            break;
        case 9:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
            break;
        case 10:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
            break;
        case 11:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));
            break;
        case 12:
            result = summation(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]));
            break;
        default:
            printf("Error: The number of arguments in summation is more than 12.\n");
            printf("Show more information: ./main -h or ./main --help\n");
            return -1;
        }
        printf("result: %.3lf\n", result.value);
    } else if (strcmp(argv[1], "-") == 0 || strcmp(argv[1], "sub") == 0) {
        if (argc != 4) {
            printf("Error: The number of arguments in subtraction is more than 4.\n");
            printf("Show more information: ./main -h or ./main --help\n");
            return -1;
        }
        printf("result: %.3lf\n", subtraction(atof(argv[2]), atof(argv[3])).value);
    } else if (strcmp(argv[1], "*") == 0 || strcmp(argv[1], "mul") == 0) {
        switch (argc)
        {
        case 4:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]));
            break;
        case 5:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]));
            break;
        case 6:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
            break;
        case 7:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
            break;
        case 8:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
            break;
        case 9:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
            break;
        case 10:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
            break;
        case 11:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));
            break;
        case 12:
            result = multiplication(argc - 2, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]));
            break;
        default:
            printf("Error: The number of arguments in multiplication is more than 12.\n");
            printf("Show more information: ./main -h or ./main --help\n");
            return -1;
        }
        printf("result: %.3lf\n", result.value);
    } else if (strcmp(argv[1], "/") == 0 || strcmp(argv[1], "div") == 0) {
        if (argc != 4) {
            printf("Error: The number of arguments in division is more than 4.\n");
            printf("Show more information: ./main -h or ./main --help\n");
            return -1;
        }
        
        result = division(atof(argv[2]), atof(argv[3]));
        
        if (result.status == -1) {
            printf("Error: divide by 0.\n");
            printf("Show more information: ./main -h or ./main --help\n");
            return -1;
        }

        printf("result: %.3lf\n", result.value);
    } else {
        printf("Error: command not found.\n");
        printf("Show more information: ./main -h or ./main --help\n");
        return -1;
    }
    return 0;
}

void info() {
    printf("More infromation\n");
    printf("Keys:\n");
    printf("\t-h or --help: show more information\n");
    printf("Calculation:\n");
    printf("\t./main <comand> <op1> <op2> <op3> ... <op10>\n");
    printf("\t<op1> <op2> <op3> ... <op10> - maximum 10 operators for summation and multiplication commands\n");
    printf("\t<op1> <op2> - maximum 2 operators for subtraction and division commands\n");
    printf("\t<commands>:\n");
    printf("\t* \"add\" or \"+\" - summation,\n");
    printf("\t* \"sub\" or \"-\" - subtraction,\n");
    printf("\t* \"mul\" or \"*\" - multiplication,\n");
    printf("\t* \"div\" or \"/\" - division,\n");
}