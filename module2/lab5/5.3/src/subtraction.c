#include <stdarg.h>

typedef struct Operator {
    double value;
    int status;
} Operator;

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
