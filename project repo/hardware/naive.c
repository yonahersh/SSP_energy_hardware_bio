#include <stdio.h>
#include "helpers.c"
int subsetWithIndex(int set[], int setLen, int target, size_t indexes)
{
    size_t mask = 1;
    int i;
    int sum = 0;
    for(i=0; i<setLen; i++)
    {
        if (indexes & mask){
            sum += set[i];
        }
        mask = mask <<1;
    }
    return sum == target;
}

int subsetWithIndexSets(int set[], int setLen, size_t indexes)
{
    size_t mask = 1;
    int i;
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

int subsetSumNaive(int set[], int setLen, int target)
{
    size_t indexes;
    size_t tempI = 1;
    double pct;
    for(indexes = 0; indexes < (tempI << setLen); indexes ++)
    {
        pct = indexes * 1.0/ (tempI << setLen);
        if(subsetWithIndex(set, setLen, target, indexes))
        {
            return 1;
        }
        
    }
    return 0;
}

int subsetSumNaiveSets(int set[], int setLen, FILE* all_sets)
{
    size_t indexes;
    size_t tempI = 1;
    double pct;
    for(indexes = 0; indexes < (tempI << setLen); indexes ++)
    {
        pct = indexes * 1.0/ (tempI << setLen);
        fprintf(all_sets, "%d\n", subsetWithIndexSets(set, setLen, indexes));
        
    }
    return 0;
}

// int main()
// {
    
//     int set[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
//     int x = subsetSumNaive(set, 30, -1);
//     printf("%d", x);

//     return 0;
// }
