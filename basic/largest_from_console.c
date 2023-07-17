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
void check(int n)
{
  int n1,n2,j=0,i=0;
  char lin1[100]={0},lin2[100];
  for(j=0;j<n;j++)
  {
      gets(lin2);
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
    printf("no.of lines\n");
    scanf("%d ",&n);
    check(n);
}
