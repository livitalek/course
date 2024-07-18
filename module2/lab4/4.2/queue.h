#include <stdint.h>

#ifndef H_QUEUE
#define H_QUEUE

typedef struct Data {
    uint32_t first;
    uint32_t second;
} Data;


typedef struct Node {
    Data data;
    uint8_t priority;
    struct Node* next;
    struct Node* prev;
} Node;

int push(Data data, uint8_t priority);
int pop(Node *data, uint8_t priority, char operation[10]);
int seek(Node *data, uint8_t priority, char operation[10]);

int is_empty();
int size();
int free_all();

#endif