#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define KEY 12341234
void main() {
    int sharedMemoryId = shmget(KEY, 0, 0);
    struct shmid_ds buffer;
    if (shmctl(sharedMemoryId, IPC_STAT, &buffer) == -1) {
        perror("Sikertelen adat lekérdezés\n");
        exit(-1);
    }   
}
