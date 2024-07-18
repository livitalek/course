#include <stdarg.h>

typedef struct Operator {
    double value;
    int status;
} Operator;

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

