#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#define KEY 123456
void main() {    
    pid_t process1;
    pid_t process2;
    pid_t process3;
    process1 = fork();
    if (process1 == 0) {        
        int sharedMemoryId = shmget(KEY, 256, IPC_CREAT | 0666);
        if (sharedMemoryId == -1) {
            perror("Memória lefoglalás sikertelen\n");
            exit(-1);
        }
        printf("Processz 1 sikeresen lefoglalta a memóriát\n");
    } else {
        process2 = fork();
        if (process2 == 0) {
            printf("Processz 2 olvas...\n");
            int sharedMemoryId = shmget(KEY, 0, 0);
            char *s = shmat(sharedMemoryId, NULL, SHM_RND);
            strlen(s) > 0 ? printf("Osztott memóriában a szöveg : %s\n", s) : printf("Nincs szöveg az osztott memóriában\n");
            //beleirunk
            strcpy(s, "Sample Text");
            printf("Processz 2 sikeresen elküldte az üzenetet\n");
        } else {
            process3 = fork();
            if (process3 == 0) {
                printf("Processz 3 \n");
                int sharedMemoryId = shmget(KEY, 0, 0);
                struct shmid_ds buffer;
                if (shmctl(sharedMemoryId, IPC_STAT, &buffer) == -1) {
                    perror("Hiba\n");
                    exit(-1);
                }
                printf("Szegmens méret: %ld\n", buffer.shm_segsz);
                printf("Utolsó processz PID-je : %d\n", buffer.shm_lpid);               
            }
        }
    }   
}
