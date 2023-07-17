#include<stdio.h>
void recur (int n) //..........T(n)
{
    if(n>0) //..................1
    {
        printf("%d ",n); //..........1
        recur(n-1); //...............T(n-1)
        recur(n-1); //...............T(n-1)
    }
    printf("\n");
}
int main()
{
    int n=5;
    recur(n);
}