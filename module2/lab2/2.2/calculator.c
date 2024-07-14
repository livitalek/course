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

Operator subtraction(int count, ...) {
    Operator result = {0, 0};
    if (count != 2) {
        result.status = -1;
        return result;
    }
    va_list args;
    va_start(args, count);
    result.value = va_arg(args, double) - va_arg(args, double);
    va_end(args);
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

Operator division(int count, ...) {
    Operator result = {0, 0};
    if (count != 2) {
        result.status = -1;
        return result;
    }
    va_list args;
    va_start(args, count);
    double op1 = va_arg(args, double);
    double op2 = va_arg(args, double);
    if (op2 == 0) {
        result.status = -1;
        return result;
    }
    result.value = op1 / op2;
    return result;
}

Operator power(int count, ...) {
    Operator result = {1, 0};
    if (count != 2) {
        result.status = -1;
        return result;
    }
    va_list args;
    va_start(args, count);
    double op1 = va_arg(args, double);
    double op2 = va_arg(args, double);
    if (op2 == 0) {
        return result;
    } else if (op2 > 0) {
        while (op2--)
        {
            result.value *= op1;
        }
        
    } else {
        while (op2++)
        {
            result.value /= op1;
        }
        
    }
    return result;
}