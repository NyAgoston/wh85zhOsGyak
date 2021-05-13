#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define KEY 12341234
void main() {
    int sharedMemoryId = shmget(KEY, 256, IPC_CREAT | 0666);   
}
