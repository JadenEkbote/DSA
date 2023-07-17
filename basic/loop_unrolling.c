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
    start=clock();
    printf("hello you idiot\n");
    for(int i=0;i<99999;i++)
    {
       a[i]=rand();
    }
    for(int i=0;i<99999;i=i+4)
    {
       a[i]=a[i]+5;
       a[i+1]=a[i+1]+5;
       a[i+2]=a[i+2]+5;
       a[i+3]=a[i+3]+5;
       a[i+4]=a[i+4]+5;

    }
    display(a);
     stop=clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    printf("time taken: %f\n",time_r);
}
