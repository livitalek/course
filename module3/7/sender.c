#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_NAME "/chat_queue"
#define MAX_SIZE 512
#define EXIT_MESSAGE "exit"

int main(int argc, char* argv[]) {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Отправить сообщение (или 'exit' для выхода): ");
        fgets(buffer, MAX_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, EXIT_MESSAGE) == 0) {
            mq_send(mq, EXIT_MESSAGE, strlen(EXIT_MESSAGE) + 1, 0);
            break;
        }

        mq_send(mq, buffer, strlen(buffer) + 1, 0);
        sleep(1);
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME); 
    return 0;
}
