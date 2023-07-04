#include<stdio.h>
#include<stdlib.h>
#define SI 100
struct queue
{
    int data[SI],front,rear;
};

void enqueue(struct queue *qptr,int num,FILE *fp2)
{
    if(qptr->rear==SI-1)
    {
        printf("Queue Overflow\n");
    }
    else
    {
        qptr->rear++;
        qptr->data[qptr->rear]=num;
        fprintf(fp2,"%d\n",num);
    }
}
int dequeue(struct queue *qptr, FILE *fp3)
{
    int num=-999;
    if(qptr->front==qptr->rear)
    {
        return num;
    }
    else
    {
        qptr->front++;
        num=qptr->data[qptr->front];
        fprintf(fp3,"%d\n",num);
    }
}
int check(char str[])
{
    if(str[0]=='d')
    {
        return 3;
    }
    else 
    {
        return 4;
    }
}
void put_stack(struct queue *qptr,FILE *fp4)
{ 
    int i;
    if(qptr->rear==-1)
    {
        printf("Stack empty\n");
    }
    else
    {
        for(i=qptr->front;i>=0;i--)
        {
            fprintf(fp4,"%d\n",qptr->data[i]);
        }
    }

}
 int main()
 {
    struct queue * qptr;
    struct queue q;
    qptr=&q;
    qptr->front=qptr->rear=-1;
    int n,h,l,x,j,k;
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    FILE *fp5;
    FILE *fp6;
    char str[100];
    fp=fopen("input.txt","r+");
    fp5=fopen("enq_deq_input.txt","r+");
    fp6=fopen("op_queue.txt","r+");
    scanf("%d%d%d",&x,&h,&l);
    for(int i=0;i<x;i++)
    {
       n=rand()%(h-l)+l;
       fprintf(fp,"%d\n",n);
    }
    rewind(fp);
    while(!feof(fp5))
    {
        fp2=fopen("log_enq.txt","a");
        fp3=fopen("log_deq.txt","a");
        fp4=fopen("queue.txt","w");
        put_stack(qptr,fp4);
        fclose(fp4);
        fscanf(fp5,"%s ",str);
        fscanf(fp5,"%d",&h);
        int ch,i,j=0;
        ch=check(str);
        //printf("1.PUSH  2.POP 3.DISPLAY 4.EXIT\n");
        //scanf("%d",&ch);
        switch(ch)
        {
            case 4: for(i=0;i<h;i++)
                    {
                        fscanf(fp,"%d",&n);
                        enqueue(qptr,n,fp2);
                        j++;
                    }
                    fprintf(fp6,"enqueue operation - %d times\n",j);
                    break;
            case 3: for(i=0;i<h;i++)
                     {
                        dequeue(qptr,fp3);
                        j++;
                     }
                     fprintf(fp6,"dequeue operation - %d times\n",j);
                    break;
            default : j=0;
                    break;
        }
        fclose(fp2);
        fclose(fp3);
    }
    //display(sptr); 
    fclose(fp5); 
    fclose(fp6);
 }