#pragma once
#include <stdint.h>
#include <stdlib.h>
#define SEED 10

void merge(int arr[], size_t l, size_t m, size_t r, FILE* logFile)
{
    size_t i, j, k;
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
    
    /* create temp arrays */
    int * L = (int *) malloc (sizeof(int) * n1);
    int * R = (int *) malloc (sizeof(int) * n2);
    fprintf(logFile, "Allocated to array Left: %d bytes, for array Right %d bytes\n", sizeof(int) * n1,sizeof(int) * n2);

  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L); free(R);
    fprintf(logFile, "Freed set Left, Right\n");
}
  
void mergeSort(int arr[], size_t l, size_t r, FILE* log)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        size_t m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m, log);
        mergeSort(arr, m + 1, r, log);
  
        merge(arr, l, m, r, log);
    }
}

int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
   
  }

int binarySearch(int arr[], size_t l, size_t r, size_t x)
{
    if (r >= l) {
        size_t mid = l + (r - l) / 2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
}

int butterflyT(int * L1, int * L2, size_t len, int target, FILE* log)
{
    size_t index1 = 0, index2 = 0;
    qsort(L1, len, sizeof(int), cmpfunc);
   // mergeSort(L1, 0, len-1, log);
    for(index2 = 0; index2 < len; index2++)
    {
        if (binarySearch(L1, 0, len - 1, target - L2[index2]) >= 0)
        {
            return 1;
        }
        
    }
    return 0;
}

int sumWithIndex(int set[], size_t setLen, size_t indexes)
{
    size_t mask = 1;
    size_t i;
    int sum = 0;
    for(i=0; i<setLen; i++)
    {
        if (indexes & mask){
            sum += set[i];
        }
        mask = mask <<1;
    }
    return sum; 
}

int * makeL(int set[], int setLen, FILE* logFile)
{
    size_t lengthL = 1;
    int * L = (int *) malloc((lengthL << setLen) * sizeof(int));
    fprintf(logFile, "Allocated for set L %d bytes\n", (lengthL << setLen) * sizeof(int));
    size_t indexes;
    size_t lIndex = 0;
    for (indexes = 0; indexes < (lengthL << setLen); indexes ++)
    {
        L[lIndex] = sumWithIndex(set, setLen, indexes);
        lIndex ++;
    }
    return L;
}

int * createSetWithTarget(int setSize, int * target,FILE * log)
{
    int recordTime = time(0);
    srand(SEED);
    size_t indexes = rand();
    indexes = indexes << 32;
    indexes |= rand();
    
    int * set = (int *) malloc (sizeof(int) * setSize);
    for(int i=0; i<setSize; i++)
    {
        set[i] = rand()%5000;
    }
    *target = sumWithIndex(set, setSize, indexes);
    
    //log this mem allocation
    fprintf(log, "at time: %ld this set was allocated:\n\t",time(0));
    for (int i=0; i<setSize; i++)
    {
    	fprintf(log, "%d ,", set[i]);
    }
    fprintf(log, "\nAnd the target is %d\n", *target);
    return set;
}



int * createSetWithTargetChangingInput(int setSize, int * target, int inputSize, FILE* log)
{
    srand(SEED);
    size_t indexes = rand();
    indexes = indexes << 32;
    indexes |= rand();
    
    int * set = (int *) malloc (sizeof(int) * setSize);
    for(int i=0; i<setSize; i++)
    {
        set[i] = rand()%inputSize;
    }
    *target = sumWithIndex(set, setSize, indexes);
    
    //log this mem allocation
    fprintf(log, "At time: %ld this set was allocated:\n\t",time(0));
    for (int i=0; i<setSize; i++)
    {
    	fprintf(log, "%d,", set[i]);
    }
    
    fprintf(log, "\nAnd the target is %d", *target);
    return set;
}
