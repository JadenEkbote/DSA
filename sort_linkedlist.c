#include <stdio.h>
#include <time.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *link;
};
struct node *newnode;

struct node *create_node()
{
    newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL)
    {
        printf("NO memory allocated");
    }
    newnode->link = NULL;
    return newnode;
}
struct node *insert_end(struct node *head,FILE *fp)
{
    int n;
    while(!feof(fp))
    {
        fscanf(fp,"%d",&n);
    struct node *cur=NULL;
    newnode = create_node();
    newnode->data=n;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        cur = head;
        while (cur->link != NULL)
        {
            cur = cur->link;
        }
        cur->link = newnode;
    }
    }
    return head;
}

void display(struct node *head)
{
    struct node *cur=NULL;
    if (head == NULL)
    {
        printf("List empty\n");
    }
    else
    {
        cur = head;
        while (cur != NULL)
        {
            printf("%d->", cur->data);
            cur = cur->link;
        }
    }
    printf("\n");
}

void bubble(struct node *head,int n)
{
    struct node *cur=head;
    struct node *prev=NULL;
    int temp;
    for(int i=0;i<n;i++)
    {
        while(cur->link!=NULL)
            {
                prev=cur;
                cur=cur->link;
                if(cur->data<prev->data)
                    {
                        temp=prev->data;
                        prev->data=cur->data;
                        cur->data=temp;
                    }
            }
            cur=head;
            prev=NULL;
    }
}
void file_back(struct node * head,FILE * fp)
{
    int e;
    printf("press one to write the sorted list to the file\n");
    scanf("%d",&e);
    if(e==1)
    {
        rewind(fp);
        int a=0;
        struct node *cur = head;
        while(cur!=NULL)
        {
            a=cur->data;
            fprintf(fp,"%d->",a);
            cur=cur->link;   
        }
    }
    
}

int main()
{
    while(1)
    {
    struct node *head = NULL;
    clock_t start,stop;
    int n,h,l,x;
    FILE *fp;
    FILE *fp2;
    fp2=fopen("log.txt","r+");
    fp=fopen("new.txt","r+");
    scanf("%d%d%d",&x,&h,&l);
    for(int i=0;i<x;i++)
    {
       n=rand()%(h-l)+l;
       fprintf(fp,"%d\n",n);
    }
    rewind(fp);
    head = insert_end(head,fp);
    display(head);
    printf("\n");
     start = clock();
    bubble(head,n);
    stop = clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    display(head);
    file_back(head,fp);
    while(!feof(fp2))
    {
        char str[1000];
        fgets(str,100,fp2);
    }
    fprintf(fp2,"%d random numbers take\t %f second(s) of time\n",x,time_r);
    fclose(fp);
    fclose(fp2);
    }
}

