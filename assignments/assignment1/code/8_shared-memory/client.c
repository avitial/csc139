/*
File: consumer.c
CSC139 
Fall 2016
First Assignment
Avitia, Luis
Section #
OS: Linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SHM_SIZE 8192

// Global pointer to the shared memory block
// This should receive the return value of mmap
// Don't change this pointer in any function
void* gShmPtr;

int main()
{
/*	
	int shm_fd;
	key_t key;
	char *shm, *s;
	key = 9876;

	// function to attach shared memory block
	shm_fd = shmget(key, SHM_SIZE, 0666);
	if(shm_fd < 0){
		perror("shmget");
		exit(1);
	}

	// attached shared memory  
	gShmPtr = shmat(shm_fd, NULL, 0);
	if(gShmPtr == (char *) -1){
		perror("shmat");
		exit(1);
	
	}
	// read from shared memory block
	for(s = gShmPtr; *s != 0; s++)
		printf("%c", *s);

	printf("\n");
	shm = (char*)gShmPtr;
	*shm = '*';	

	
	return 0;	
*/
	int shm_fd;
	key_t key;
	char *shm, *s;
	const char *name = "OS_HW1_Luis_Avitia"; // Name of shared memory object to be passed to shm_open

	// function to attach shared memory block
	shm_fd = shm_open(name, O_RDWR, 0666);
	if(shm_fd < 0){
		perror("shm_open");
		exit(1);
	}

	// attached shared memory  
	gShmPtr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(gShmPtr == (char *) -1){
		perror("mmap");
		exit(1);
	}
	
	// read from shared memory block
	printf("%s", (char *)gShmPtr);
	printf("\n");

	// attached shared memory  
	gShmPtr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(gShmPtr == (char *) -1){
		perror("mmap");
		exit(1);
	}
	// write to shared memory block
	sprintf(gShmPtr, "%c", '*');
	

	// remove the shared memory segment 
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}
	return 0;	
}
