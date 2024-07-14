#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

void info();

const Dict commands[5] = {
    {'+', "sum", summation},
    {'-', "sub", subtraction},
    {'*', "mul", multiplication},
    {'/', "div", division},
    {'^', "pow", power}
};


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
    int i;
    Operator result;
    for (i = 0; i < 5; i++) {
        if(argv[1][0] == commands[i].key || strcmp(argv[1], commands[i].str) == 0) {
            switch (argc)
            {
            case 4:
                result = commands[i].func(2, atof(argv[2]), atof(argv[3]));
                break;
            case 5:
                result = commands[i].func(3, atof(argv[2]),  atof(argv[3]), atof(argv[4]));
                break;
            case 6:
                result = commands[i].func(4, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]));
                break;
            case 7:
                result = commands[i].func(5, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
                break;
            case 8:
                result = commands[i].func(6, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
                break;
            case 9:
                result = commands[i].func(7, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
                break;
            case 10:
                result = commands[i].func(8, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
                break;
            case 11:
                result = commands[i].func(9, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));
                break;
            default:
                result = commands[i].func(10, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]));
                break;
            }
        }
    }
    
    if (result.status == -1) {
        printf("Error: Operation error.\n");
        printf("Show more information: ./main -h or ./main --help\n");
    } else {
        printf("result: %.3lf\n", result.value);
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