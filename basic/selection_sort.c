#include<stdio.h>
#include<stdlib.h>
void read(int a[100], int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
}
void selection_sort(int a[], int n)
{
    int  temp, temp2;
     long min = 999999999;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                temp = j;
            }
        }
        temp2 = a[temp];
        a[temp] = a[i];
        a[i] = temp2;
        min = 999;
    }
    print(a,n);
}
void print(int a[100], int n)
{
    int i;
    for(i=0;i<n;i++)

    {
        printf("%d ",a[i]);
    }

}
int main ()
{
    int n;
    FILE *fptr;
    fptr=fopen("text.txt","r");
    printf("enter size\n");
    scanf("%d",&n);
    read(a,n);
    bubble_sort(a,n);
}

