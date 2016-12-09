#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 100

int main(int argc, char *argv[]){
	int shmid;
	key_t key;
	char *shm, *s;
	key = 9876;

	// function to attach shared memory block
	shmid = shmget(key, SHM_SIZE, 0666);
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}

	// attached shared memory  
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat");
		exit(1);
	
	}
	// read from shared memory block
	for(s = shm; *s != 0; s++)
		printf("%c", *s);

	printf("\n");
	
	*shm = '*';	

	
	return 0;	
}
