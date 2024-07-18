#include <stdarg.h>

typedef struct Operator {
    double value;
    int status;
} Operator;

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
