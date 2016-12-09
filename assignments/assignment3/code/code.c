#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int roundRobin(int time_quantum, int processes, void *param);


int main(){
	int cnt,j,n,time,procs,flag=0,time_quantum, pid, arrival_time, burst_time, priority; 
	int wait_time=0,turnaround_time=0, at[10], bt[10], rt[10];
	char algorithm[20];
	// Variables to read from file
	FILE* file = fopen ("/home/leavitia/Dropbox/Documentos/Ezequiel/SacState/F16/CSC139/assignments/assignment3/code/input.txt", "r");
	int i=0, m;
	char c;
	
	// Determine cpu scheduling algorithm
	while ((c = fgetc(file)) != ' '){
		algorithm[i] = c;
		i++;
	}
	if (strcmp(algorithm,"RR") == 0){
		fscanf (file, "%d", &i);
		time_quantum = i;
	}
	// Determine number of procs from second line
	fscanf (file, "%d", &i);
	procs = i;
	int pinfo[procs][5];
	
	// Determine procs arrival time, burst time and priority
	for(n=1; n<=procs; n++){
		fscanf (file, "%d", &i);
		pinfo[n][0] = i;
		for(m=1; m<4; m++){
			fscanf (file, "%d", &i);
			pinfo[n][m] = i;
		}
	}
//	printf("Algorithm[%s]\t",algorithm);
	if (strcmp(algorithm,"RR") == 0){
		printf("Round Robin\n");
		// Determine time quantum
		roundRobin(time_quantum, procs, &pinfo[1][0]);
	}
	else if (strcmp(algorithm,"SJF") == 0)
		printf("SJF\n");
	else if (strcmp(algorithm,"PR_noPREMP") == 0)
		printf("PR_noPREMP\n");
	else if (strcmp(algorithm,"PR_withPREMP") == 0)
		printf("PR_withPREMP\n");
	else
		printf("Invalid algorithm entry\n");
	
	fclose (file);
	for(cnt=0; cnt<procs; cnt++){
	}
	return 0;
}

int roundRobin(int time_quantum, int processes, void *param) {
	int tq = time_quantum, cnt, j, n, time, flag=0;
	int procs = processes;
	int *ptr = (int *)param;
	int process = *ptr; //ptr++;
	int arrival_t = *ptr+1; //ptr++;
	int burst_t = *ptr+2; //ptr++;
	int priority = *ptr+3;
	
	
	for(int i=0; i<procs; i++){
		printf("Process[%d]\t", process); // Process
		printf("Arrival time %d\t", arrival_t); // Arrival time
		printf("Burst time %d\t", burst_t); // Burst time
		printf("Priority %d\n", priority); // Priority
		process = *ptr; ptr++;
		arrival_t = *ptr; ptr++;
		burst_t = *ptr; ptr++;
		priority = *ptr;ptr++;
	}	
	return 0;
}