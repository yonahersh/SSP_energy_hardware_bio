#include <time.h>
#include <stdint.h>
#include "horowitz.c"
#include "naive.c"
#include "dynamic.c"

#define TRIES_PER_SIZE 500
#define MIN_INPUT_SIZE 100000
#define MAX_INPUT_SIZE 100000000000 


void compareRunTimeWithSizeChangingInput(FILE * logsFile, int setSize, int inputSize)
{
    int target = 0;
    int * set = createSetWithTargetChangingInput(setSize, &target, inputSize);

    int i;
    double time_taken;
    clock_t t;
    double  dynamicTime = 0, naiveTime = 0;

    for (i = 0; i < TRIES_PER_SIZE; i++)
    {

        t = clock();
	subsetSumDynamic(set, setSize, target);
        t = clock() - t;
        dynamicTime += ((double)t)/CLOCKS_PER_SEC; // in seconds

        t = clock();
     	subsetSumNaive(set, setSize, target);
        t = clock() - t;
        naiveTime += ((double)t)/CLOCKS_PER_SEC; // in seconds
    }
    
    
    fprintf(logsFile,"%d,", inputSize);
    fprintf(logsFile,"%f,", dynamicTime/TRIES_PER_SIZE);
    fprintf(logsFile,"%f\n", naiveTime/TRIES_PER_SIZE);
    fflush(logsFile);
    free(set);
}
int main()
{
    int i;
    FILE * logsFile = fopen("subset_sum_time_input_size_change_100000-100000000000_take2.csv", "w");
    fprintf(logsFile, "Input size,Dynamic,Naive\n");
    for (int i = MIN_INPUT_SIZE; i <= MAX_INPUT_SIZE; i+=100000) 
    {       
        compareRunTimeWithSizeChangingInput(logsFile,35, i);
    }
    fclose(logsFile);
    return 0;
}
