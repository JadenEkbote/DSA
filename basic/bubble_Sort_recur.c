#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void bubble(int a[], int n)
{
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            bubble(a, n - 1);
            if (a[n - 1] > a[n])
            {
                int temp = a[n - 1];
                a[n - 1] = a[n];
                a[n] = temp;
            }
        }
    }
}
int main()
{
    int a[5] = {5, 4, 2, 7, 1}, n;
    bubble(a, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
}