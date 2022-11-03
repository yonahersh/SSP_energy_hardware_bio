#include <time.h>
#include "horowitz.c"
#include "naive.c"
#include "dynamic.c"

int generatedTest();
int genarateManyTests()
{
    int recordTime = time(0);
    
    srand(recordTime);
    int i;
    for (i = 0; i<10; i++ )
    {
        if (!generatedTest())
        {
	    printf("%d recorded time\n", recordTime);	
            return 0;
        }
    }
    return 1;
}
int generatedTest()
{
    int indexes = rand();
    int set[40];
    int setSize = 40;
    for(int i=0; i<setSize; i++)
    {
        set[i] = rand()%100;

    }
    int target = sumWithIndex(set, setSize, indexes);
    // printf("%d\n", indexes);
    // printf("target = %d\nrecordTime = %d\n", target, recordTime);
    int result = subsetSumHorowitz(set, setSize, target) + subsetSumDynamic(set, setSize, target)+ subsetSumNaive(set, setSize, target);// + subsetSumShamir(set, setSize, target);
    if (result !=3 )
    {
        return 0;
    }
    return 1;
}

int staticTests()
{
    int set[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
    
    int setSize = 40;
    int target = 150;
    int result = subsetSumHorowitz(set, setSize, target) + subsetSumDynamic(set, setSize, target)+ subsetSumNaive(set, setSize, target);// + subsetSumShamir(set, setSize, target);
    if(result != 3)
    {
        return 0;
    }

    target = -1;
    result = subsetSumHorowitz(set, setSize, target) + subsetSumDynamic(set, setSize, target)+ subsetSumNaive(set, setSize, target);// + subsetSumShamir(set, setSize, target);
    if(result != 0)
    {
        return 0;
    }

    target = 1000;
    result = subsetSumHorowitz(set, setSize, target) + subsetSumDynamic(set, setSize, target)+ subsetSumNaive(set, setSize, target);// + subsetSumShamir(set, setSize, target);
    if(result != 0)
    {
        return 0;
    }

    target = 1;
    result = subsetSumHorowitz(set, setSize, target) + subsetSumDynamic(set, setSize, target)+ subsetSumNaive(set, setSize, target);// + subsetSumShamir(set, setSize, target);
    if(result != 3)
    {
        return 0;
    }

    return 1;
}
int main()
{
    if (!staticTests())
    {
        printf("failure on static\n");
        return 1;
    }
    if(!genarateManyTests())
    {
        printf("failure on generated\n");
        return 1;
    }
    printf("success\n");
    return 0;
}
