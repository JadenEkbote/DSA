#include<stdio.h>
#include<stdlib.h>
int count(char str[100])
{
    int i,n;
    while(str[i]!='\0')
    {
        n++;
        i++;
    }
    return n;
}
void check(int n,FILE *fptr)
{
  int n1,n2,i=0;
  char lin1[100]={0},lin2[100];
  while(!feof(fptr))
  {
      fgets(lin2,100,fptr);
      n1=count(lin1);
      n2=count(lin2);
      if(n1<n2)
      {
          while(lin2[i]!='\0')
          {
              lin1[i]=lin2[i];
              i++;
          }
          i=0;
      }
  }
  printf("%s\n",lin1);

}
int main()
{
    int n;
    FILE *fptr;
    fptr=fopen("text.txt","r");
    fscanf(fptr,"%d",&n);
    printf("%d\n",n);
    check(n,fptr);
    fclose(fptr);
}
