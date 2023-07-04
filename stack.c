#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#define SIZE 100
struct stack
{
    int data[SIZE];
    int top;
};

void push(struct stack *sptr, int num,FILE *fp2)
{
    if(sptr->top==SIZE-1)
    {
        printf("Stack Overflow\n");
    }
    else
    {
        sptr->top++;
        sptr->data[sptr->top]=num;
        fprintf(fp2,"%d\n",num);
    }
}
void pop(struct stack *sptr,FILE *fp3)
{
    int num;
    if(sptr->top==-1)
    {
        printf("Stack underflow\n");
    }
    else
    {
        num=sptr->data[sptr->top];
        sptr->top--;
        fprintf(fp3,"%d\n",num);
    }
    printf("%d\n",num);
}

void display(struct stack *sptr)
{
    int i;
    if(sptr->top==-1)
    {
        printf("Stack empty\n");
    }
    else
    {
        for(i=sptr->top;i>=0;i--)
        {
            printf("\n%d\n",sptr->data[i]);
        }
    }
}

void put_stack(struct stack *sptr,FILE *fp4)
{ 
    int i;
    if(sptr->top==-1)
    {
        printf("Stack empty\n");
    }
    else
    {
        for(i=sptr->top;i>=0;i--)
        {
            fprintf(fp4,"%d\n",sptr->data[i]);
        }
    }

}
 int main()
 {
    struct stack * sptr;
    struct stack s;
    sptr=&s;
    sptr->top=-1;
    int n,h,l,x;
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    fp=fopen("input.txt","r+");
    scanf("%d%d%d",&x,&h,&l);
    for(int i=0;i<x;i++)
    {
       n=rand()%(h-l)+l;
       fprintf(fp,"%d\n",n);
    }
    rewind(fp);
    while(1)
    {
        fp2=fopen("logpush.txt","a");
        fp3=fopen("logpop.txt","a");
        fp4=fopen("stack.txt","w");
        put_stack(sptr,fp4);
        fclose(fp4);
        int ch,i;
        printf("1.PUSH  2.POP 3.DISPLAY 4.EXIT\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: fscanf(fp,"%d",&n);
                    push(sptr,n,fp2);
                    break;
            case 2: pop(sptr,fp3);
                    break;
            case 3: display(sptr);
                    break;
            case 4: exit(0);
                    break;
            default : printf("inavlid\n");
                    break;
        }
        fclose(fp2);
        fclose(fp3);
    }
    
 }