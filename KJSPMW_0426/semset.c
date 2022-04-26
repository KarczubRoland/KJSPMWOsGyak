
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 432763R

	int semid,	
	    nsems,	
	    semnum,	
	    rtn;	

	int semflg;	
	struct sembuf sembuf, *sop; 
	union semun arg; 
	int cmd;	

main()
{


	nsems = 1;	
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n kerem a semval erteket ");

	semnum = 0;	

	cmd = SETVAL;	
	scanf("%d",&arg.val);
	rtn = semctl(semid,semnum, cmd, arg);

	printf("\n set  rtn: %d ,semval: %d ",rtn,arg.val);
	printf("\n");

}