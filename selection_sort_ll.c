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

int count(struct node * head)
{
    int n=0;
    struct node * cur=head;
    while(cur!=NULL)
    {
        n++;
        cur=cur->link;
    }
    //printf("%d\n",n);
    return n;
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

struct node* selection(struct node *head)
{
    int n;
    n = count(head);
   // printf("%d\n",n);
    struct node *cur=head;
    struct node *cur1=head;
    struct node *pos=NULL;
    int temp=__INT_MAX__;
    int swap=0;
    for(int i=0;i<n;i++)
    {

        cur=cur1;
        while(cur!=NULL)
            {
                if(cur->data<temp)
                    {
                       // printf("i have come\n");
                        temp=cur->data;
                        pos=cur;
                    }
                    cur=cur->link;
            }
                swap=cur1->data;
                cur1->data=pos->data;
                pos->data=swap;
                cur1=cur1->link;
                temp=__INT_MAX__;
    }
    return head;
}
void file_back(struct node * head,FILE * fp)
{
    int e;
    printf("press 1 to write the sorted list to the file\n");
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
    struct node *head = NULL;
    clock_t start,stop;
    int n,h,l,x;
    FILE *fp;
     FILE *fp2;
    fp=fopen("new.txt","r+");
    fp2=fopen("log.txt","w");
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
    head = selection(head);
    stop = clock();
    float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    fprintf(fp2,"sorted list selection\t\t %f\n",time_r);
    display(head);
    file_back(head,fp);
    fclose(fp);
    fclose(fp2);
}
