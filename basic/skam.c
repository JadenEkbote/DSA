#include<stdio.h>

int minimum(int a[],int n)
{
    int min=__INT_MAX__; //assign max value at the start to find the minimum value
    int i;
    for(i=0;i<n;i++) //executing the loop until the end of the array!
    {
        if(a[i]<min)// checking wether any value present in array is lower than the previous value
        {
            min = a[i]; // assign the minimum value to min.
        }
    }
    return min;// returning the minimum value from the array!
}
 int main()
 {
    int a[100],n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    i=0;
    i=minimum(a,n);
    printf("%d\n",i);
 }
