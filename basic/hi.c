#include<stdio.h>
#include<stdlib.h>
int index=0;
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
int check(char lin[], char pat[100])
{
    int i=0,j=0,n1,n2,status=1;
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
                   
                    if(lin[i+j] == pat[j])
                    {
                       status=1;
                       break;
                    }
                    else
                    {
                        status=0;
                        break;
                    }
                     j++;
                }
                if(status==1)
                {
                    index=i;
                    printf("%s\n",lin);
                    break;
                }
            }
            i++;
        }
        return status;
 }
 void replace(char lin[],char pat[],char str[],FILE *fp,FILE *temp)
 {

    int i=0,j=0;
   // while(str[i]!='\0')
    //{
         while(pat[i]!='\0')
         {
            lin[index+i]=pat[i];
            i++;
         }
        /*if(lin[index+i]==str[i])
         {
            lin[index+i]=' ';
         }
         i++;*/
   // }
    printf("%s\n",lin);
   fprintf(temp,"%s",lin);
 }
int main()
{
    int stat;
    char rem[100],lin[100],pat[100];
    FILE *fp, *temp;
    fp=fopen("new.txt","r+");
    temp=fopen("wow.txt","w");
    printf("enter pattern to be changed\n");
    scanf("%s",rem);
    printf("enter the new pattern to be added\n");
    scanf("%s",pat);
    while(!feof(fp))
    {
       fgets(lin,100,fp);
       stat=check(lin,rem);
       if(stat==1)
       {
        replace(lin,pat,rem,fp,temp);
       }
    }
    fclose(fp);

}
