/*
File: MTFindMin_template.c
CSC139 
Fall 2016
Second Assignment
Avitia, Luis
Section #
OS: Linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <semaphore.h>

#define MAX_SIZE 100000000
#define MAX_THREADS 16
#define RANDOM_SEED 97751
#define MAX_RANDOM_NUMBER 5000

// Global variables
long gRefTime; //For timing
int gData[MAX_SIZE]; //The array that will hold the data

int gThreadCount; //Number of threads
int gDoneThreadCount; //Number of threads that are done at a certain point. Whenever a thread is done, it increments this. Used with the semaphore-based solution
int gThreadMin[MAX_THREADS]; //The minimum value found by each thread
bool gThreadDone[MAX_THREADS]; //Is this thread done? Used when the parent is continually checking on child threads

// Semaphores
sem_t completed; //To notify parent that all threads have completed or one of them found a zero
sem_t mutex; //Binary semaphore to protect the shared variable gDoneThreadCount

int SqFindMin(int size); //Sequential FindMin (no threads)
void *ThFindMin(void *param); //Thread FindMin but without semaphores 
void *ThFindMinWithSemaphore(void *param); //Thread FindMin with semaphores 
int SearchThreadMin(); // Search all thread minima to find the minimum value found in all threads 
void GenerateInput(int size, int indexForZero); //Generate the input array 
void CalculateIndices(int arraySize, int thrdCnt, int indices[MAX_THREADS][3]); //Calculate the indices to divide the array into T divisions, one division per thread
void InitSharedVars(); // Function to initialize shared variables used by threads
int GetRand(int min, int max);//Get a random number between min and max

//Timing functions
long GetMilliSecondTime(struct timeb timeBuf);
long GetCurrentTime(void);
void SetTime(void);
long GetTime(void);

int main(int argc, char *argv[]){

	pthread_t tid[MAX_THREADS];  
	pthread_attr_t attr[MAX_THREADS];
	int indices[MAX_THREADS][3];
	int i, indexForZero, arraySize, min;

	// Code for parsing and checking command-line arguments
	if(argc != 4){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}
	if((arraySize = atoi(argv[1])) <= 0 || arraySize > MAX_SIZE){
		fprintf(stderr, "Invalid Array Size\n");
		exit(-1);				
	}
	gThreadCount = atoi(argv[2]);				
	if(gThreadCount > MAX_THREADS || gThreadCount <=0){
		fprintf(stderr, "Invalid Thread Count\n");
		exit(-1);				
	}
	indexForZero = atoi(argv[3]);
	if(indexForZero < -1 || indexForZero >= arraySize){
		fprintf(stderr, "Invalid index for zero!\n");
		exit(-1);
	}

    GenerateInput(arraySize, indexForZero);

    CalculateIndices(arraySize, gThreadCount, indices); 

	// Code for the sequential part
	SetTime();
	min = SqFindMin(arraySize);
	printf("Sequential search completed in %ld ms. Min = %d\n", GetTime(), min);
	

	// Threaded with parent waiting for all child threads
	SetTime();

	// Write your code here
	// Initialize threads, create threads, and then let the parent wait for all threads using pthread_join
	// The thread start function is ThFindMin
	// Don't forget to properly initialize shared variables 

	
	
    min = SearchThreadMin();
	printf("Threaded FindMin with parent waiting for all children completed in %ld ms. Min = %d\n", GetTime(), min);

	// Multi-threaded with busy waiting (parent continually checking on child threads without using semaphores)
	SetTime();

	// Write your code here
    // Don't use any semaphores in this part	
	// Initialize threads, create threads, and then make the parent continually check on all child threads
	// The thread start function is ThFindMin
	// Don't forget to properly initialize shared variables 

	
    min = SearchThreadMin();
	printf("Threaded FindMin with parent continually checking on children completed in %ld ms. Min = %d\n", GetTime(), min);
	

	// Multi-threaded with semaphores  
	SetTime();

    // Write your code here
	// Initialize threads, create threads, and then make the parent wait on the "completed" semaphore 
	// The thread start function is ThFindMinWithSemaphore
	// Don't forget to properly initialize shared variables and semaphores using sem_init 


	
	min = SearchThreadMin();
	printf("Threaded FindMin with parent waiting on a semaphore completed in %ld ms. Min = %d\n", GetTime(), min);
}

// Write a regular sequential function to search for the minimum value in the array gData
int SqFindMin(int size) {
	int min = MAX_RANDOM_NUMBER + 1;
	int location = 1;
	int i;
	for(i=0; i<size; i++){
		if ( gData[i] < min){
			min = gData[i];
			location = i+1;
		}
	}
	// printf("Min element is at location %d, it's value is %d.\n", location, min);
	return min;
}

// Write a thread function that searches for the minimum value in one division of the array
// When it is done, this function should put the minimum in gThreadMin[threadNum] and set gThreadDone[threadNum] to true    
void* ThFindMin(void *param) {
	int threadNum = ((int*)param)[0];
	
}

// Write a thread function that searches for the minimum value in one division of the array
// When it is done, this function should put the minimum in gThreadMin[threadNum]
// If the minimum value in this division is zero, this function should post the "completed" semaphore
// If the minimum value in this division is not zero, this function should increment gDoneThreadCount and
// post the "completed" semaphore if it is the last thread to be done
// Don't forget to protect access to gDoneThreadCount with the "mutex" semaphore     
void* ThFindMinWithSemaphore(void *param) {

}

int SearchThreadMin() {
    int i, min = MAX_RANDOM_NUMBER + 1;
	
    for(i =0; i<gThreadCount; i++) {
                if(gThreadMin[i] == 0)
                        return 0;
		if(gThreadDone[i] == true && gThreadMin[i] < min)
			min = gThreadMin[i];
	}
	return min;
}

// Write a function that fills the gData array with random numbers between 1 and MAX_RANDOM_NUMBER
// If indexForZero is valid and non-negative, set the value at that index to zero 
void GenerateInput(int size, int indexForZero) {
	int i;
	for(i = 0; i< size; i++){
		gData[i] = GetRand(1,MAX_RANDOM_NUMBER);
	}
	gData[indexForZero] = 0;
}

// Write a function that calculates the right indices to divide the array into thrdCnt equal divisions
// For each division i, indices[i][0] should be set to the division number i,
// indices[i][1] should be set to the start index, and indices[i][2] should be set to the end index 
void CalculateIndices(int arraySize, int thrdCnt, int indices[MAX_THREADS][3]) {
	int i,j;
	
	for(i=0; i<thrdCnt; i++){
		for(j=0; j<=2; j++){
			// threadNo
			if(j==0){
				indices[i][j] = i;
				printf("indices[%d][%d] = %d\t",i,0,indices[i][0]);
			}
			// beginIndex
			else if(j==1){ 
				indices[i][j] = (arraySize/thrdCnt)*i;
				printf("indices[%d][%d] = %d\t",i,j,indices[i][j]);		
			}
			// endIndex
			else{
				indices[i][j] = (arraySize/thrdCnt)*(i+1)-1;
				printf("indices[%d][%d] = %d\n",i,j,indices[i][j]);		
			}
		}
	}
}

// Function to initialize shared variables used by threads
void InitSharedVars() {
	int i;
	for(i=0; i<gThreadCount; i++){
		gThreadDone[i] = false; 
		gThreadMin[i] = MAX_RANDOM_NUMBER + 1;  
	}
	gDoneThreadCount = 0;
}

// Get a random number in the range [x, y]
int GetRand(int x, int y) {
    int r = rand();
    r = x + r % (y-x+1);
    return r;
}

long GetMilliSecondTime(struct timeb timeBuf){
	long mliScndTime;
	mliScndTime = timeBuf.time;
	mliScndTime *= 1000;
	mliScndTime += timeBuf.millitm;
	return mliScndTime;
}

long GetCurrentTime(void){
	long crntTime=0;
	struct timeb timeBuf;
	ftime(&timeBuf);
	crntTime = GetMilliSecondTime(timeBuf);
	return crntTime;
}

void SetTime(void){
	gRefTime = GetCurrentTime();
}

long GetTime(void){
	long crntTime = GetCurrentTime();
	return (crntTime - gRefTime);
}
