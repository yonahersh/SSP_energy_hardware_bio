#include <time.h>
#include <stdint.h>
#include "horowitz.c"
#include "naive.c"
#include "dynamic.c"
#include <string.h>

#define MIN_SET_SIZE 5
#define MAX_SET_SIZE 40 
#define TRIES_PER_SIZE 20

void compareRunTimeWithSize(FILE * resultsFile, int setSize, FILE* logFile)
{
    int target = 0;
    int * set = createSetWithTarget(setSize, &target, logFile);

    int i;
    double time_taken;
    clock_t t;
    double horowtitzTime = 0, dynamicTime = 0, naiveTime = 0;

    for (i = 0; i < TRIES_PER_SIZE; i++)
    {
        t = clock();
        subsetSumHorowitz(set, setSize, target, logFile);
        t = clock() - t;
        horowtitzTime += ((double)t)/CLOCKS_PER_SEC; // in seconds

     
        t = clock();
	subsetSumNaive(set, setSize, target);
        t = clock() - t;
        naiveTime += ((double)t)/CLOCKS_PER_SEC; // in seconds
    }
    
    fprintf(resultsFile,"%d,", setSize);
    fprintf(resultsFile,"%f,", horowtitzTime/TRIES_PER_SIZE);
    
    fprintf(resultsFile,"%f\n", naiveTime/TRIES_PER_SIZE);
    
    fflush(resultsFile);
    
    fprintf(logFile,"\nfreeing set\n\n");
    
    free(set);
}


int main()
{
    int i;
    char fileName[100];
    sprintf( fileName, "/home/hershky1/results/subset_sum_time_traces_%d-%d.csv",MIN_SET_SIZE, MAX_SET_SIZE);
    
    FILE * resultsFile = fopen(fileName, "w");
    
    sprintf( fileName, "/home/hershky1/logs/logs_subset_sum_time_traces_%d-%d.txt", MIN_SET_SIZE, MAX_SET_SIZE);
    FILE * logs = fopen(fileName, "w");
    fprintf(logs, "starting running at %ld\n**************\n",time(0) );
    fprintf(resultsFile, "Input size,Horowitz,Naive\n");
    
    for (int i = MIN_SET_SIZE; i <= MAX_SET_SIZE; i+= 2)
    {   
    	printf("set size: %d\n", i);  
	fflush(stdout);
    	fprintf(logs, "Set size: %d\n", i);
        compareRunTimeWithSize(resultsFile, i,logs);
    }
    
    //fprintf(logs, "\n****************\nfinished running at %ld",time(0) );
    fclose(logs);
    fclose(resultsFile);
    return 0;
}
