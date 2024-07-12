#ifndef H_CALCULATOR
#define H_CALCULATOR

typedef struct Operator {
    double value;
    int status;
} Operator;

Operator summation(int count, ...);
Operator subtraction(double op1, double op2);
Operator multiplication(int count, ...);
Operator division(double op1, double op2);

#endif