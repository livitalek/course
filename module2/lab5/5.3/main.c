#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include <dlfcn.h>

void info();

const Dict commands[5] = {
    {'+', "sum", "summation"},
    {'-', "sub", "subtraction"},
    {'*', "mul", "multiplication"},
    {'/', "div", "division"},
    {'^', "pow", "power"}
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

    void* handle;
    char* error;
    char string[128];
    for (i = 0; i < 5; i++) {
        sprintf(string, "lib/lib%s.so", commands[i].command);
        handle = dlopen(string, RTLD_LAZY);
        if (!handle) {
            fputs(dlerror(), stderr);
            printf("\n");
            exit(1);
        }
        function = dlsym(handle, commands[i].command);

        if(argv[1][0] == commands[i].key || strcmp(argv[1], commands[i].str) == 0) {
            switch (argc)
            {
            case 4:
                result = function(2, atof(argv[2]), atof(argv[3]));
                break;
            case 5:
                result = function(3, atof(argv[2]),  atof(argv[3]), atof(argv[4]));
                break;
            case 6:
                result = function(4, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]));
                break;
            case 7:
                result = function(5, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]));
                break;
            case 8:
                result = function(6, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
                break;
            case 9:
                result = function(7, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
                break;
            case 10:
                result = function(8, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]));
                break;
            case 11:
                result = function(9, atof(argv[2]),  atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));
                break;
            default:
                result = function(10, atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]), atof(argv[11]));
                break;
            }
        }
        dlclose(handle);
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