#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node* head = NULL;
Node* tail = NULL;

int push(Data data, uint8_t priority) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->priority = priority;
    node->next = NULL;
    node->prev = NULL;

    Node *current = tail;
    Node *temp;

    if (is_empty()) {
        head = tail = node;
    } else if (current->priority <= node->priority &&
                current == tail) {
        tail->next = node;
        node->prev = tail;
        tail = node;
    } else {
        while (current != head)
        {
            if((current->priority <= node->priority) &&
                (node->priority < current->next->priority)
            ) {
                temp = current->next;
                temp->prev = node;
                current->next = node;
                node->next = temp;
                node->prev = current;
                break;
            }

            current = current->prev;
        }
        if (current == head) {
            if (current->priority <= node->priority) {
                temp = current->next;
                temp->prev = node;
                current->next = node;
                node->next = temp;
                node->prev = current;
            } else {
                head->prev = node;    
                node->next = head;
                head = node;
            }
        }
    }
    return 0;
}

int pop(Data* data, uint8_t priority, char operation[10]) {
    Node* current = head;
    Node* temp;
    if (!is_empty()) {
        while (current != NULL) {
            if ( (strcmp(operation, "==") == 0 && current->priority == priority) ||
                (strcmp(operation, "!=") == 0 && current->priority != priority) ||
                (strcmp(operation, "<=") == 0 && current->priority <= priority) ||
                (strcmp(operation, ">=") == 0 && current->priority >= priority) ||
                (strcmp(operation, "<") == 0 && current->priority < priority) ||
                (strcmp(operation, ">") == 0 && current->priority > priority)
            ) {
                break;
            }            
            current = current->next;
        }

        if (current == NULL) {
            return -1;
        }
        
        *data = current->data;
        
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        if (head == current) {
            head = current->next;
        }

        if (head == NULL) {
            tail = NULL;
        }

        free(current);
        return 0;
    }
    return -1;
}

int seek(Data *data, uint8_t priority, char operation[10]) {
    Node* current = head;
    if (!is_empty()) {
        while (current != NULL) {
            if ( (strcmp(operation, "==") == 0 && current->priority == priority) ||
                (strcmp(operation, "!=") == 0 && current->priority != priority) ||
                (strcmp(operation, "<=") == 0 && current->priority <= priority) ||
                (strcmp(operation, ">=") == 0 && current->priority >= priority) ||
                (strcmp(operation, "<") == 0 && current->priority < priority) ||
                (strcmp(operation, ">") == 0 && current->priority > priority)
            ) {
                break;
            }            
            current = current->next;
        }

        if (current == NULL) {
            return -1;
        }
        *data = current->data;
        return 0;
    }
    return -1;
}

int is_empty() {
    return head == NULL;
}

int size() {
    int counter = 0;
    Node* current = head;
    while (current != NULL) {
        counter++;
        current = current->next;
    }
    return counter;
}

int free_all() {
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = tail = NULL;    
}

