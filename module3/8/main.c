#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_SEM 2
#define SEM_READ 0
#define SEM_WRITE 1

int my_random();

//static int can_access_file;

key_t key;
int sems_id;

int count;

int pipefd[2];
int fd;


char msg[4];
char msg1[4];
int i, t;


void P(int semid, int sem_num); // --
void V(int semid, int sem_num); // ++


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error:\n%s <count>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    count = atoi(argv[1]);

    if (count <= 0) {
        printf("Error:\nCount can be greater then 0.\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((key  = ftok("file.txt", 'A')) < 0) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    if ((sems_id = semget(key, MAX_SEM, 0666 | IPC_CREAT)) < 0) {
        perror("segment");
        exit(EXIT_FAILURE);
    }

    if (semctl(sems_id, SEM_READ, SETVAL, 0) < 0) {
        perror("semctl - SETVAL read");
        exit(EXIT_FAILURE);
    }

    if (semctl(sems_id, SEM_WRITE, SETVAL, 0) < 0) {
        perror("semctl - SETVAL write");
        exit(EXIT_FAILURE);
    }

    V(sems_id, SEM_WRITE);

    for (t = 0; t < 2; t++) {

        printf("SEM_READ %d\n", semctl(sems_id, SEM_READ, GETVAL));
        printf("SEM_WRITE %d\n", semctl(sems_id, SEM_READ, GETVAL));

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            
            close(pipefd[0]);
            if (semctl(sems_id, SEM_WRITE, GETVAL) == 0) {
                
                printf("child sem read: %d\n", semctl(sems_id, SEM_READ, GETVAL));

                if ((fd = open("file.txt", O_CREAT | O_RDONLY, 0666)) < 0) {
                    perror("Error: open");
                    exit(EXIT_FAILURE);
                }

                int number_from_file;

                while (read(fd, &number_from_file, sizeof(int)) > 0) {
                    printf("File: %d\n", number_from_file);
                }
                close(fd);
                V(sems_id, SEM_WRITE);
                P(sems_id, SEM_READ);
                printf("child:\n");
                printf("SEM_READ %d\n", semctl(sems_id, SEM_READ, GETVAL));
                printf("SEM_WRITE %d\n", semctl(sems_id, SEM_READ, GETVAL));

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
            }
            exit(EXIT_SUCCESS);
        } else {
            close(pipefd[1]);
            if (semctl(sems_id, SEM_READ, GETVAL) == 0) {
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
//                    printf("t: %d ", t);
                    printf("Received: %d\n", received_number);

                    write(fd, &received_number, sizeof(int));
                }
                close(fd);
                V(sems_id, SEM_READ);
                P(sems_id, SEM_WRITE);
                printf("parent:\n");
                printf("SEM_READ %d\n", semctl(sems_id, SEM_READ, GETVAL));
                printf("SEM_WRITE %d\n", semctl(sems_id, SEM_READ, GETVAL));
            }
            close(pipefd[0]);
        }
    }
    semctl(sems_id, SEM_READ, IPC_RMID);
    semctl(sems_id, SEM_WRITE, IPC_RMID);
    exit(EXIT_SUCCESS);
}

int my_random() {
    return (rand() << 16) | rand();
}

void P(int semid, int sem_num) {
    struct sembuf sb = {sem_num, -1, 0};
    if (semop(semid, &sb, 1) < 0) {
        perror("sempop - p");
        exit(EXIT_FAILURE);
    }
}
void V(int semid, int sem_num) {
    struct sembuf sb = {sem_num, 1, 0};
    int buf = 0;
    if ((buf = semop(semid, &sb, 1)) < 0) {
        perror("sempop - v");
        exit(EXIT_FAILURE);
    }
    printf("buf: %d\n", buf);
}