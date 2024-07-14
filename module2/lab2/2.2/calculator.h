#include<string.h>

#ifndef H_CALCULATOR
#define H_CALCULATOR

typedef struct Operator {
    double value;
    int status;
} Operator;

typedef Operator (*function) (int, ...);

typedef struct Dict {
    char key;
    char str[10];
    function func;
} Dict;

//commands
Operator summation(int count, ...);
Operator subtraction(int count, ...);
Operator multiplication(int count, ...);
Operator division(int count, ...);
Operator power(int count, ...);

#endif