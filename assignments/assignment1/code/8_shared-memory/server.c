/*
File: producer.c
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

// Function calls
void Producer(int, int, int);
void InitShm(int, int, int);
int GetRand(int, int);

int main(int argc, char *argv[]){
	pid_t pid;
	char *shm, *s;
	
	int bufSize; // Bounded buffer size
	int itemCnt; // Number of items to be produced
	int randSeed; // Seed for the random number generator 
	
	if(argc != 4){
		printf("Invalid number of command-line arguments, enter buffer size and items to be produced.\n");
		exit(1);
    }
	
	bufSize = atoi(argv[1]);
	itemCnt = atoi(argv[2]);
	randSeed = atoi(argv[3]);
	
    // Function that creates a shared memory segment and initializes its header
    InitShm(bufSize, itemCnt, randSeed);        

	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n");
		exit(1);
	}
	else if (pid == 0) { /* child process */
		printf("Launching Client \n");
		execlp("./client.o","client",NULL);
	}
	else { /* parent process */
		/* parent will wait for the child to complete */
		printf("Starting Server\n");
	}
	shm = (char*)gShmPtr;
	while(*shm != '*')
		sleep(1);	
	return 0;	
}

void InitShm(int bufSize, int itemCnt, int randSeed)
{
	/*
	int shm_fd;
	pid_t pid;
	key_t key;
	int val, lenght;
	char str[3];
	char *s;
	key = 9876;	
	const char *name = "OS_HW1_Luis_Avitia"; // Name of shared memory object to be passed to shm_open
	
	// function to create shared memory block
	shm_fd = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
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
	
	srand(randSeed);
	val = GetRand(0,500);
	sprintf(str, "%d", val);
	lenght = sizeof str; 
	
	// write to shared memory block
	memcpy(gShmPtr, str, lenght);

	s = gShmPtr;
	s += lenght;
	*s = 0;
	*/
	int shm_fd;
	int val, lenght;
	char str[3];
	char *s;
	const char *name = "OS_HW1_Luis_Avitia"; // Name of shared memory object to be passed to shm_open
	
	// function to create shared memory block
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	if(shm_fd < 0){
		perror("shm_open");
		exit(1);
	}
	ftruncate(shm_fd,SHM_SIZE);
	// attached shared memory  
	gShmPtr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(gShmPtr == (char *) -1){
		perror("mmap");
		exit(1);
	}
	
	srand(randSeed);
	val = GetRand(0,500);
	sprintf(str, "%d", val);
	lenght = sizeof str; 
	sprintf(gShmPtr, "%s", str);
	
	s = gShmPtr;
	s += lenght;
	*s = 0;
	
}

void Producer(int bufSize, int itemCnt, int randSeed)
{
	int in = 0;
	int out = 0;
	
	srand(randSeed);

	// Write code here to produce itemCnt integer values in the range [0-500]
	// Use the functions provided below to get/set the values of shared variables "in" and "out"
	// Use the provided function WriteAtBufIndex() to write into the bounded buffer 	
	// Use the provided function GetRand() to generate a random number in the specified range
	// **Extremely Important: Remember to set the value of any shared variable you change locally
	// Use the following print statement to report the production of an item:
	// printf("Producing Item %d with value %d at Index %d\n", i, val, in);
	// where i is the item number, val is the item value, in is its index in the bounded buffer
	//WriteAtBufIndex(GetIn(),GetRand(0, 500));	
	//Producer(bufSize, itemCnt, randSeed);
	printf("Producer Completed\n");
}

// Get a random number in the range [x, y]
int GetRand(int x, int y)
{
        int r = rand();
        r = x + r % (y-x+1);
        return r;
}