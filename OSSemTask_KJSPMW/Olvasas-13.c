#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 85L
int main()
{
	int shmid;
	key_t key;		
	int size=512;		
	int shmflg;	
	struct struktura {
		int  hossz;
		char szoveg[512-sizeof(int)]; 

	} *segm;		/* Epp a szegmensre kepezzuk ezt a strukturat.*/

	key = SHMKEY;

	shmflg = 0;	/* Nincs IPC_CREAT, feltetelezzuk, az shmcreate.c
				keszitett osztott memoria szegmenst */

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget system-call sikertelen volt!\n");
	    exit(-1);
	}

/* Rakapcsolodunk az attach-ra.*/

	shmflg = 00666 | SHM_RND;
	segm = (struct struktura *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}

/* Az osztott memoria ott lesz a "segm" cimen, ha az attach sikeres volt.
   Ha van benne valami, akkor azt kiiratom, utana billentyuzetrol kerek uj szoveget */

	if (strlen(segm->szoveg) > 0)
		printf("\nRegi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
	int rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Hibakod: %d\n", rtn);
		return 0;
		}
