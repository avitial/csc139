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

	// function to create shared memory block
	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
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
	// write to shared memory block
	memcpy(shm, "Hello World!", 12);

	s = shm;
	s += 12;
	*s = 0;	

	while(*shm != '*')
		sleep(1);	
	
	return 0;	
}
