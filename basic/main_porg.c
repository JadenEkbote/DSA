#include <stdio.h>
#include <time.h>
#include "sorting.h"

void input(FILE *fp1)
{
    int n, x, l, h;
    printf("Enter n,lower,higher\n");
    scanf("%d %d %d", &n, &l, &h);
    for (int i = 0; i < n; i++)
    {
        int temp = rand() % (h - l) + l;
        fprintf(fp1, "%d ", temp);
    }
}

void copy_arr(int a[], int x, FILE *fp)
{
    int n;
    for (int i = 0; i < x; i++)
    {
        fscanf(fp, "%d", &n);
        a[i] = n;
    }
}

void file_output(FILE *fp2, int a[], int x)
{
    for (int i = 0; i < x; i++)
    {
        fprintf(fp2, "%d ", a[i]);
    }
}

void sorting(int a[], int x, FILE *fp1, FILE *fp2)
{
    clock_t start, stop;
    FILE *fp3 = fopen("log.txt", "w");
    fputs("Sort Tec\t\tTime\n", fp3);
    start = clock();
    bubble_sort(a, x);
    stop = clock();
    rewind(fp1);
    copy_arr(a, x, fp1);
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    fprintf(fp3, "bubble sort\t\t%f\n", time_r);
    start = clock();
    selection_sort(a, x);
    stop = clock();
    rewind(fp1);
    copy_arr(a, x, fp1);
    time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    fprintf(fp3, "selection sort\t%f\n", time_r);
    start = clock();
    mergeSort(a, 0, x - 1);
    stop = clock();
    time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    fprintf(fp3, "merge sort\t\t%f", time_r);
    file_output(fp2, a, x);
}

int main()
{
    int x;
    FILE *fp1 = fopen("input.txt", "w+");
    input(fp1);
    rewind(fp1);
    printf("Enter X number to be sorted:");
    scanf("%d", &x);
    int a[x];
    copy_arr(a, x, fp1);
    FILE *fp2 = fopen("output.txt", "w");
    fputs("sorted output:", fp2);
    sorting(a, x, fp1, fp2);
}
