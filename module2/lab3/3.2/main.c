#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


#define RUGO S_IRUSR | S_IRGRP | S_IROTH;
#define WUGO S_IWUSR | S_IWGRP | S_IWOTH;
#define XUGO S_IXUSR | S_IXGRP | S_IXOTH;

void print_mode(__mode_t mode);
__mode_t update_mode(__mode_t current_mode, char target[10], char operation, char action[10]);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("./main <[ugo|a][+=-][rwx]> <file>\n");
        return -1;
    }
    int i;
    char* token[2];
    char operation;
    struct stat status;
    stat(argv[2], &status);
    printf("Current mode for %s.\n", argv[2]);
    print_mode(status.st_mode);
    for(i = 0; i < strlen(argv[1]) ; i++) {
        if (argv[1][i] == '+' || argv[1][i] == '=' || argv[1][i] == '-') {
            operation = argv[1][i];
            break;
        }
    
    }
    token[0] = strtok(argv[1], "+-=");
    token[1] = strtok(NULL, "+-=");
    __mode_t mode = update_mode(status.st_mode, token[0], operation, token[1]);
    printf("Update mode for %s.\n", argv[2]);
    print_mode(mode);
    return 0;
}

void print_mode(__mode_t mode) {
    printf("Bit view: %o\n", mode & 0777);
    printf("Symbol view: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

__mode_t update_mode(__mode_t current_mode, char target[10], char operation, char action[10]) {
    __mode_t mode = 0;
    __mode_t target_m = 0;
    __mode_t action_m = 0;
    int i;
    for (i = 0; i < strlen(target); i++) {
        switch (target[i]) {
        case 'a':
            target_m |= S_IRWXU | S_IRWXG | S_IRWXO;
            break;
        case 'u':
            target_m |= S_IRWXU;
            break;
        case 'g':
            target_m |= S_IRWXG;
            break;
        case 'o':
            target_m |= S_IRWXO;
            break;
        default:
            printf("Don't understand target %c.\n", target[i]);
            exit(EXIT_FAILURE);
            return -1;
        }
    }

    for (i = 0; i < strlen(action); i++) {
        switch (action[i]) {
        case 'r':
            action_m |= RUGO;
            break;
        case 'w':
            action_m |= WUGO;
            break;
        case 'x':
            action_m |= XUGO;
            break;
        default:
            printf("Don't understand action %c.\n", target[i]);
            exit(EXIT_FAILURE);
            return -1;
        }
    }
    if (operation != '=') {
        switch (operation)
        {
        case '+':
            mode = current_mode | target_m & action_m;
            break;
        case '-':
            mode = current_mode & ~(target_m & action_m);
            break;
        default:
            printf("Don't understand operation %c.\n", operation);
            exit(EXIT_FAILURE);
            return -1;
        }
    } else {
        mode = current_mode;
        if ((target_m & action_m & S_IRWXU) != 0) {
            mode &= (S_IRWXG | S_IRWXO);
        }
        if ((target_m & action_m & S_IRWXG) != 0) {
            mode &= (S_IRWXU | S_IRWXO);
        }
        if ((target_m & action_m & S_IRWXO) != 0) {
            mode &= (S_IRWXU | S_IRWXG);
        }
        mode |= (target_m & action_m);
    }
    return mode;
}

