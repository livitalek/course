#include <stdio.h>
#include "queue.h"

int main(int argc, char* argv[]) {
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    printf("push (Data) {1, 1}, priority: 10\n");
    push((Data) {1, 1}, 10);
    printf("push (Data) {2, 2}, priority: 20\n");
    push((Data) {2, 2}, 20);
    printf("push (Data) {3, 2}, priority: 30\n");
    push((Data) {3, 3}, 30);
    printf("push (Data) {4, 4}, priority: 10\n");
    push((Data) {4, 4}, 10);
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    printf("size = %d\n", size());
    Node data;
    int out;
    out = seek(&data, 20, "==");
    printf("(%d)data[%d] = {%d, %d} == 20\n", out, data.priority, data.data.first, data.data.second);
    out = seek(&data, 20, "!=");
    printf("(%d)data[%d] = {%d, %d} != 20\n", out, data.priority, data.data.first, data.data.second);
    out = seek(&data, 20, ">=");
    printf("(%d)data[%d] = {%d, %d} >= 20\n", out, data.priority, data.data.first, data.data.second);
    out = seek(&data, 20, "<=");
    printf("(%d)data[%d] = {%d, %d} <= 20\n", out, data.priority, data.data.first, data.data.second);
    out = seek(&data, 20, ">");
    printf("(%d)data[%d] = {%d, %d} > 20\n", out, data.priority, data.data.first, data.data.second);
    out = seek(&data, 20, "<");
    printf("(%d)data[%d] = {%d, %d} < 20\n", out, data.priority, data.data.first, data.data.second);
    printf("size = %d\n", size());
    printf("pop data != 20\n");
    out = pop(&data, 20, "!=");
    printf("(%d)data[%d] = {%d, %d}\n", out, data.priority, data.data.first, data.data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data[%d] = {%d, %d}\n", out, data.priority, data.data.first, data.data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data[%d] = {%d, %d}\n", out, data.priority, data.data.first, data.data.second);
    out = pop(&data, 20, "!=");
    printf("(%d)data[%d] = {%d, %d}\n", out, data.priority, data.data.first, data.data.second);
    printf("size = %d\n", size());
    free_all();
    printf("size = %d\n", size());
    printf(is_empty() ? "%s" : "not %s", "empty\n");
    return 0;
}