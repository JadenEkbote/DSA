#include<stdio.h>
void recur (int n) //..........T(n)
{
    if(n>0) //..................1
    {
        printf("%d\t",n); //..........1
        recur(n-1); //...............T(n-1)
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    recur(n);
}