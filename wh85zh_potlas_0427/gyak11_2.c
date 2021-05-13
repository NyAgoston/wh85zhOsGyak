#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L
	int semid, nsems, semnum, rtn;
	int semflg;
	struct sembuf sembuf, *sop;
	union semun arg;
	int cmd;

main()
{
	// Elso
	nsems = 1;	/* egyetlen semaphore a set-ben */
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n kerem a semval erteket ");

	semnum = 0;	/* 0-i semaphort azonositom */

	cmd = SETVAL;	/* allitsd be a semaphor erteket */
	scanf("%d",&arg.val);
	rtn = semctl(semid,semnum, cmd, arg); /* a semid-vel azonositott set 0-ik semaphorat ! */

	printf("\n set  rtn: %d ,semval: %d ",rtn,arg.val);
	printf("\n");

	// Masodik
	cmd = GETVAL;	/* E parancsra a semctl visszaadja a currens semaphor erteket. Itt az rtn-be.  */
	rtn = semctl(semid,0, cmd, NULL);

	printf("\n semval: %d ",rtn);
	printf("\n");

    // Harmadik
	cmd = IPC_RMID;		/* Ez a megszuntetes parancsa */
	rtn = semctl(semid,0, cmd, arg);

	printf("\n kill rtn: %d ",rtn);
	printf("\n");

    // Negyedik
	nsops = 1;		/* Egy operacio van */
	sembuf.sem_num = 0;	/* A 0-ik semaphor-ral foglakozunk */
	sembuf.sem_op = 1;	/* Inkrementaciot kerunk! */
	sembuf.sem_flg = 0666;	/* Flag beallitas */
	sop = &sembuf;		/* Igy keri a semop az argumentumot */
	rtn = semop(semid, sop, nsops);
		/* 0-val visszatero semop sikeres. */
	printf("\n up rtn: %d ",rtn);
	printf("\n");

}
