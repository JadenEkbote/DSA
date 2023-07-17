#include<stdio.h>
#include<stdlib.h>
int count(char str[100])
{
    int n=0,i=0;
    while (str[i] != '\0')
    {
        n++;
        i++;
    }
    return n;
}

void check(FILE *fptr, char pat[100])
{
    int i=0,j=0,n1,n2,status;
    char lin[100];
    while(!feof(fptr))
    {
        fgets(lin,100,fptr);
        n1=count(lin);
        n2=count(pat);
        i=0;
        j=0;
        status=0;
        while(lin[i]!='\0')
        {
            if(lin[i]==pat[j])
            {
                j++;
                while(j<n2-1)
                {

                    if(lin[i+j]==pat[j])
                    {
                       status=1;
                       j++;
                    }
                    else
                    {
                        status=0;
                        break;
                    }
                }
                if(status==1)
                {
                    printf("%s\n",lin);
                    break;
                }
            }
            i++;
        }
 }
}
int main()
{
    FILE *fptr;
    char pat[100];
    fptr=fopen("text.txt","r");
    fgets(pat,100,fptr);
    printf("%s\n",pat);
    check(fptr,pat);
    fclose(fptr);
}
