#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void display(int a[])
{
    int i ;
    for(i=0;i<99999;i++)
    {
        printf("%d\t",a[i]);
    }
}
int main()
{
    int a[100000];
    clock_t start,stop;
    for(int i=0;i<99999;i++)
    {
       a[i]=rand();
    }
    start=clock();
    for(int i=0;i<99999;i++)
    {
       a[i]=a[i]+5;
    }
    display(a);
    stop=clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    printf("\ntime taken: %f\n",time_r);
}
