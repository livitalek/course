#include <stdarg.h>

typedef struct Operator {
    double value;
    int status;
} Operator;

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
