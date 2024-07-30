#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

int my_random();

static int can_access_file;

void sigusr1_handler(int signo);
void sigusr2_handler(int signo);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error:\n%s <count>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int count = atoi(argv[1]);

   signal(SIGUSR1, sigusr1_handler);
   signal(SIGUSR2, sigusr2_handler);

    if (count <= 0) {
        printf("Error:\nCount can be greater then 0.\n");
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char msg[4];
    char msg1[4];
    int i, t;

    for (t = 0; t < 2; t++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            
            close(pipefd[0]);
            if (can_access_file) {
                int fd = open("file.txt", O_CREAT | O_RDONLY, 0666);
                if (fd == -1) {
                    perror("Error: open");
                    exit(EXIT_FAILURE);
                }
                int number_from_file;

                while (read(fd, &number_from_file, sizeof(int)) > 0) {
                    printf("file: %d\n", number_from_file);
                }
            } else {
                int r_num;
                srand(time(NULL));
                for (i = 0; i < count; i++) {
                    r_num = my_random();
                    printf("Random: %d\n",r_num);
                    msg[0] = (r_num >> 0) & 0xFF;
                    msg[1] = (r_num >> 8) & 0xFF;
                    msg[2] = (r_num >> 16) & 0xFF;
                    msg[3] = (r_num >> 24) & 0xFF;
                    write(pipefd[1], msg, sizeof(msg));
                }
                close(pipefd[1]);
                raise(SIGUSR1);
            }
            exit(EXIT_SUCCESS);
        } else {
            close(pipefd[1]);
            if (!can_access_file) {
                int fd = open("file.txt", O_CREAT | O_WRONLY, 0666);
                if (fd == -1) {
                    perror("Error: open");
                    exit(EXIT_FAILURE);
                }
                int received_number;
                for (i = 0; i < count; i++) {
                    read(pipefd[0], msg1, sizeof(msg));
                    received_number = 0 | (unsigned char) msg1[3];
                    received_number = (received_number << 8) | (unsigned char) msg1[2];
                    received_number = (received_number << 8) | (unsigned char) msg1[1];
                    received_number = (received_number << 8) | (unsigned char) msg1[0];

                    printf("Received: %d\n", received_number);

                    write(fd, &received_number, sizeof(int));
                }
                close(fd);
                raise(SIGUSR2);
            }
            close(pipefd[0]);
        }

    }
    exit(EXIT_SUCCESS);
}

int my_random() {
    return (rand() << 16) | rand();
}

void sigusr1_handler(int signo) {
    can_access_file = 0;
}

void sigusr2_handler(int signo) {
    can_access_file = 1;
}
