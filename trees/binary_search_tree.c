#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *
newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        inorder(root->left);
        inorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        inorder(root->right);
        printf("%d ", root->key);
    }
}

// A utility function to insert
// a new node with given key in BST
struct node *insert(struct node *node, int key)
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
struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}
struct node *deleteNode(struct node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void random(FILE *fp, int n)
{
    int i, x;
    for (i = 0; i < n; i++)
    {
        x = rand() % 1000;
        fprintf(fp, "%d ", x);
    }
    rewind(fp);
}

// Driver Code
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    struct node *root = NULL;
    FILE *fp;
    int n;
    fp = fopen("trees.txt", "w+");
    printf("enter the number of elements\n");
    scanf("%d", &n);
    random(fp, n);
    for (int i = 0; i < n; i++)
    {
        int y;
        fscanf(fp, "%d", &y);
        if (root == NULL)
        {
            root = insert(root, y);
        }
        insert(root, y);
    }
    fclose(fp);
    /*root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);*/

    // Print inorder traversal of the BST
    printf("\ninorder:\n");
    inorder(root);
    printf("\npreorder:\n");
    preorder(root);
    printf("\npostorder:\n");
    postorder(root);

    printf("\nenter the node you want to delete\n");
    int m;
    scanf("%d", &m);
    root = deleteNode(root, m);

    printf("\ninorder:\n");
    inorder(root);
    printf("\npreorder:\n");
    preorder(root);
    printf("\npostorder:\n");
    postorder(root);

    return 0;
}