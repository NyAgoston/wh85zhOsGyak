#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_OF_SEMS 4

int main(void) {
  key_t key = ftok("semset.c", (int)'S');
  int flag = 00666 | IPC_CREAT;
  int num_of_sems = NUM_OF_SEMS;
  int sem_id = semget(key, num_of_sems, flag);

  if (sem_id < 0) {
    perror(" smget hiba");
    return -1;
  } else {
    printf("Semid: %d\n", sem_id);
  }

  int command = GETVAL;

  for (int i = 0; i < num_of_sems; i++) {
    int current_sem_value = semctl(sem_id, i, command, NULL);
    printf("semval %d: %d\n", i, current_sem_value);
  }

  return 0;
}
