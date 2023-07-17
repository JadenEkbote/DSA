#include<stdio.h>
#include<stdlib.h>
#include<time.h>
static inline void square (int n)
{
    int temp;
    for(int i=0;i<=n;i++)
    {
        temp=i*i;
        printf("square of %d = %d\n",i,temp);
    }
}
int main()
{
    int n;
    clock_t start,stop;
    scanf("%d",&n);
    start=clock();
    square(n);
    stop=clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    printf("\ntime taken: %f\n",time_r);
}
