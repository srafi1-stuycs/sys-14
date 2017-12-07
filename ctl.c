#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 42

void sem_create(char* input) {
    int i;
    sscanf(input, "%d", &i);
    int sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | IPC_SET | 0660);
    if (sem == -1) {
        printf("The semaphore already exists\n");
    } else {
        printf("Creating semaphore with value: %d\n", i);
        semctl(sem, 0, SETVAL, i);
    }
}

void sem_getval() {
    int sem = semget(KEY, 1, 0);
    int val = semctl(sem, 0, GETVAL, 0);
    if (val == -1) {
        printf("The semaphore does not exist\n");
    } else {
        printf("Semaphore value: %d\n", val);
    }
}

void sem_remove() {
    int sem = semget(KEY, 1, 0);
    int val = semctl(sem, 0, GETVAL, 0);
    semctl(sem, 0, IPC_RMID, 0);
    if (val == -1) {
        printf("The semaphore does not exist\n");
    } else {
        printf("Removed semaphore: %d\n", val);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: $ ./ctl -c N | -v | -r\n");
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 3) {
            printf("Usage: $ ./ctl -c N\n");
        } else {
            sem_create(argv[2]);
        }
    } else if (strcmp(argv[1], "-v") == 0) {
        sem_getval();
    } else if (strcmp(argv[1], "-r") == 0) {
        sem_remove();
    }
    return 0;
}
