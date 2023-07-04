#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void display(int a[])
{
    int i ;
    for(i=0;i<5;i++)
    {
        printf("%d\t",a[i]);
    }
}
int main()
{
    int a[1000000];
    clock_t start,stop;
    for(int i=0;i<5;i++)
    {
       a[i]=rand();
    }
    start=clock();
    for(int i=0;i<5;i++)
    {
       a[i]=a[i]+5;
    }
    stop=clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    display(a);
    printf("time taken: %f\n",time_r);
}