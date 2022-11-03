#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * makeRow(int target)
{
    int * row = (int *) malloc (sizeof(int) * (target +1));
    memset(row, 0, (sizeof(int) * (target +1)));
    row[0]  =1;
}

int subsetSumDynamic(int set[], int setLen, int target)
{
    int * row0 = makeRow(target);
    int * row1 = makeRow(target);
    int i, j; // i - runs on set, j run on all sums until target
    for (i = 0; i < setLen; i++)
    {
        for (j=1; j<target + 1; j++)
        {
            if(j < set[i] )
            {
                row1[j] = row0[j];
            }
            else
            {
                row1[j] = row0[j] || (row0[j-set[i]]);
            }
        }
        free(row0);
        row0 = row1;
        row1 = makeRow(target);
    }
    int result = row0[target];
    free(row0);
    return result;
}

// int main()
// {
//     int set[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
//     int x = subsetSumDynamic(set, 30, 50);
//     prints = {"Not Found","Found"}
//     printf("%s", prints [x]);
//     return x;
// }
