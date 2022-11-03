#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "helpers.c"

int subsetSumHorowitz(int set[], int setLen, int target, FILE * log)
{
    int * L1 = makeL(set, setLen/2, log);
    int * L2 = makeL(set + setLen/2, setLen/2, log);
    size_t length = 1;
    int result = butterflyT(L1, L2, length << (setLen/2), target, log);
    free(L1); free(L2);
    fprintf(log, "Freeing L1, L2");
    return result;
}
