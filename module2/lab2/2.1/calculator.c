#include "calculator.h"
#include <stdarg.h>

int operand1, operand2;
char command;

Operator summation(int count, ...) {
    Operator result = {0, 0};
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        result.value += va_arg(args, double);
    }
    va_end(args);
    return result;
}

Operator subtraction(double op1, double op2) {
    Operator result = {0, 0};
    result.value = op1 - op2;
    return result;
}

Operator multiplication(int count, ...) {
    Operator result = {1, 0};
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        result.value *= va_arg(args, double);
    }
    va_end(args);
    return result;    
}

Operator division(double op1, double op2) {
    Operator result = {0, 0};
    if (op2 == 0) {
        result.status = -1;
        return result;
    }
    result.value = op1 / op2;
    return result;
}
