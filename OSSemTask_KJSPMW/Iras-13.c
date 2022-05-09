#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#define SHMKEY 85L
#define KEY 24L
#define PERM 00666

int main()
{
	int shmid;		/* Osztott memoria azonosito deklaralasa */
	key_t key;		/* Kulcs az osztott memoriahoz */
	int size=512;		/* Osztott szegmens merete */
	int shmflg;		/* Flag a jellemzokhoz */
struct struktura {
		int  hossz;
		char szoveg[512-sizeof(int)]; /* Az egesz merete 512, ezert a hossz valtozot levonom a tombbol */
	} *segm;
	key = SHMKEY;

	/* Megnezem, van-e mar "size" meretu es SHMKEY kulcsu szegmens: */
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Keszitsuk el a szegmenst, mivel meg nincsen!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	} else printf("Ilyen shm szegmens mar letezik!\n");

	printf("\nAz shm szegmens azonositoja: %d \n", shmid);
	shmflg = 00666 | SHM_RND;	                                /* RND az igazitashoz */
	segm = (struct struktura *)shmat(shmid, NULL, shmflg); /* A NULL azert van ott, mert meghagyom hogy az OS dontse el, milyen cimtartomanyt hasznaljon.*/
	if (segm == (void *)-1) {
		perror("Az attach sikertelen!\n");
		exit(-1);
	}


int 	id;         /* A szemafor azonositoja */

	if ((id = semget(KEY, 1, 0)) < 0) {      /* Nem letezik meg.*/
		if ((id = semget(KEY, 1, PERM | IPC_CREAT)) < 0) {
		 	perror("Nem nyithato meg a szemafor..");
			exit(-1);
		}
	}
	else    {
		perror("Siker, a szemafor mar letezik!");
		exit(0);
	}

	if (semctl(id, 0, SETVAL, 1) < 0) {
		perror("Nem lehetett inicializálni. ");
	} else {
		puts("A szemafor kesz, es inicializalva lett!");
	}
	struct sembuf up[1]  =  {0,  1, SEM_UNDO};
struct sembuf down[1] = {0, -1, SEM_UNDO};
puts("A nem kritikus szakasz fut.");

	semop(id, down, 1);   /* Belepesi szakasz */
	puts("Kritikus szakasz itt fut éppen.");
	strcpy(segm->szoveg,"Van benne valami szoveg stb..");
	sleep(3);
	semop(id, up, 1);    /* Ez a kilepesi szakasz */
	puts("Itt ismet nem a kritikus szakasz fut. ");
	if (semctl(id, 0, IPC_RMID, 0) < 0) {
		perror("Sajnos nem sikerult torolni.");
		exit(-1);
	}

	puts("A szemafort megszuntettuk. \n");
	shmdt(segm);
	return 0;
	}


