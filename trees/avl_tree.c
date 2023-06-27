// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// An AVL tree node
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

// A utility function to get the height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b; // ternery function : its like asking ' is a>b ? '
    //(colon works like this, return this value if true : return this value if false)
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node *newNode(int key)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct node *insert(struct node *node, int key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node

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
    int i;
    // base case
    if (root == NULL)
    {
        printf("element %d not found\n", key);
        return root;
    }

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }

    // if key is same as root's key,
    // then This is the node
    // to be deleted
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

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node *temp = minValueNode(root->right);

        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void inorder(struct node *root, FILE *fp4)
{
    if (root != NULL)
    {
        inorder(root->left, fp4);
        fprintf(fp4, "%d ", root->key);
        inorder(root->right, fp4);
    }
}

void preorder(struct node *root, FILE *fp2)
{
    if (root != NULL)
    {
        fprintf(fp2, "%d ", root->key);
        inorder(root->left, fp2);
        inorder(root->right, fp2);
    }
}

void postorder(struct node *root, FILE *fp3)
{
    if (root != NULL)
    {
        inorder(root->left, fp3);
        inorder(root->right, fp3);
        fprintf(fp3, "%d ", root->key);
    }
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
void preOrder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/* Driver program to test above function*/
int main()
{
    struct node *root = NULL;
    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    int n;
    clock_t start, stop;
    start = clock();
    fp = fopen("trees.txt", "w+");
    fp2 = fopen("preorder.txt", "w+");
    fp3 = fopen("postorder.txt", "w+");
    fp4 = fopen("inorder.txt", "w+");
    printf("enter the number of elements\n");
    scanf("%d", &n);
    random(fp, n);
    while (!feof(fp))
    {
        int y;
        fscanf(fp, "%d", &y);
        root = insert(root, y);
    }
    fclose(fp);
    /* Constructing tree given in the above figure
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);*/

    /* The constructed AVL Tree would be
             30
            / \
           20  40
          / \	 \
        10  25   50
    */

    printf("\nPreorder traversal of the constructed AVL tree is \n");
    preOrder(root);
    int m;
    printf("\nenter the element to be deleted\n");
    scanf("%d", &m);
    deleteNode(root, m);
    preOrder(root);
    stop = clock();
    float t = (float)(stop - start) / CLOCKS_PER_SEC;
    inorder(root, fp4);
    preorder(root, fp2);
    postorder(root, fp3);
    printf("%d\n", root->height);
    printf("\ntime taken to create an AVL tree of %d numbers and delete %d from the tree is %f\n", n, m, t);
    return 0;
}
