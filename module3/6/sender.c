#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512
#define MESSAGE 1
#define EXIT_MESSAGE 2

typedef struct Message
{
    long msg_type;
    char text[MAX_TEXT];
} Message;

int main() {
    key_t key = ftok("chat", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid < 0) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    
    Message msg;
    while (1)
    {
        printf("Enter message (or 'exit' for exit): ");
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = 0;
        printf("Sender message: %s\n", msg.text);

        if (strcmp(msg.text, "exit") == 0) {
            msg.msg_type = EXIT_MESSAGE;
            if (msgsnd(msgid, &msg, sizeof(msg), 0) < 0 )
            exit(EXIT_SUCCESS);
        }
        msg.msg_type = MESSAGE;
        msgsnd(msgid, &msg, sizeof(msg), 0);
        sleep(1);
    }
    msgctl(msgid, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}