#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512
#define MESSAGE 1
#define EXIT_MESSAGE 2

struct message {
    long msg_type;
    char text[MAX_TEXT];
};

int main() {
    key_t key = ftok("chat", 65); 
    int msgid = msgget(key, 0666 | IPC_CREAT); 

    if (msgid < 0) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct message msg;
    while (1) {
        msgrcv(msgid, &msg, sizeof(msg), 0, 0);

        if (msg.msg_type == EXIT_MESSAGE) {
            printf("Exit...\n");
            break;
        }

        printf("Receiver message: %s\n", msg.text);
    }

    exit(EXIT_SUCCESS);
}
