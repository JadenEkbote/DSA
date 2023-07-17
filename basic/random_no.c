#include<stdio.h>
#include<stdlib.h>
int check(int x, FILE *fptr)
{
    int n,stat=1;
    while(!(feof(fptr)))
    {
        fscanf(fptr,"%d",&n);
        if(x==n)
        {
            stat=0;
        }
    }
    return stat;
}
int main()
{
    int low,high,n,x,i,stat=0;
    FILE *fptr;
    fptr=fopen("text.txt","w+");
    for(i=0;i<100;i++)
    {
        x=rand()%100;
        if(x!=0)
        {
            stat=check(x,fptr);
        }
        if(stat==1)
        {
            fprintf(fptr,"%d ",x);
        }
    }
    fclose(fptr);
}
