#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

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

    mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0'; 
            printf("Получено сообщение: %s\n", buffer);

            if (strcmp(buffer, EXIT_MESSAGE) == 0) {
                printf("Завершение общения...\n");
                break;
            }
        } else {
            perror("mq_receive");
        }
    }

    mq_close(mq);
    return 0;
}
