#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root, FILE *fp)
{
    if (root != NULL)
    {
        inorder(root->left, fp);
        fprintf(fp, "%d ", root->key);
        printf("%d ", root->key);
        inorder(root->right, fp);
    }
}
void postorder(struct node *root, FILE *fp)
{
    if (root != NULL)
    {
        postorder(root->right, fp);
        postorder(root->left, fp);
        printf("%d ", root->key);
        fprintf(fp, "%d ", root->key);
    }
}

// A utility function to insert
// a new node with given key in BST
struct node *insert(struct node *node, char key)
{
    // If the tree is empty, return a new node
    if (node == NULL)
        return newNode(key);

    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Return the (unchanged) node pointer
    return node;
}
void random(FILE *fp, int n)
{
    int r;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        r = rand() % 100;
        fprintf(fp, "%d ", r);
    }
    rewind(fp);
}
int main()
{
    int n;
    struct node *root = NULL;
    FILE *fp = fopen("random.txt", "w+");
    printf("Enter how many random numbers:\n");
    scanf("%d", &n);
    random(fp, n);
    int k = 0;
    FILE *fp1 = fopen("output.txt", "w");
    while (!feof(fp))
    {
        for (int i = 0; i < 5; i++)
        {
            int key;
            if (fp == NULL)
            {
                break;
            }
            fscanf(fp, "%d", &key);
            if (root == NULL)
            {
                root = insert(root, key);
            }
            insert(root, key);
        }
        if (k == 0)
        {
            inorder(root, fp1);
            root = NULL;
            k = 1;
        }
        else
        {
            postorder(root, fp1);
            root = NULL;
            k = 0;
        }
    }
    fclose(fp);
    fclose(fp1);

    return 0;
}
