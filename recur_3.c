#include<stdio.h>
void recur (int n) //..........T(n)
{
    if(n>0) //..................1
    {
        for(int i=1;i<n;i=i*2) //..........n+1
        {
            printf("%d ",n); //..........n
        }
        printf("\n");//.................1
        recur(n-1); //...............T(n-1)
    }              
}                   //..... T(n)=T(n-1)+n+n+1+1
int main()
{
    int n=5;
    recur(n);
}