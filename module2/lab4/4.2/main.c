#include <stdio.h>
#include "queue.h"

int main(int argc, char* argv[]) {
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    push((Data) {1, 1}, 10);
    push((Data) {2, 2}, 20);
    push((Data) {3, 3}, 30);
    push((Data) {4, 4}, 10);
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    printf("size = %d\n", size());
    Data data;
    int out;
    out = seek(&data, 20, "!=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = seek(&data, 20, "==");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = seek(&data, 20, ">=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = seek(&data, 20, "<=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = seek(&data, 20, ">");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = seek(&data, 20, "<");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    printf("size = %d\n", size());
    printf("pop\n");
    out = pop(&data, 20, "!=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data = {%d, %d}\n", out, data.first, data.second);
    printf("size = %d\n", size());
    free_all();
    printf("size = %d\n", size());
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    return 0;
}