#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    RED,
    BLACK
} nodeColor;

typedef struct Node
{
    int data;
    nodeColor color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree
{
    Node *root;
    Node *NIL; // Sentinel NIL node
} RBTree;

Node *createNode(int data, Node *NIL)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New nodes are always red initially
    newNode->left = newNode->right = newNode->parent = NIL;
    return newNode;
}

RBTree *createTree()
{
    RBTree *newTree = (RBTree *)malloc(sizeof(RBTree));
    newTree->NIL = (Node *)malloc(sizeof(Node));
    newTree->NIL->color = BLACK;
    newTree->root = newTree->NIL;
    return newTree;
}

void leftRotate(RBTree *tree, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        tree->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree *tree, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL)
    {
        tree->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

void insertFixup(RBTree *tree, Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y->color == RED)
            { // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                { // Case 2: Uncle is black and z is right child
                    z = z->parent;
                    leftRotate(tree, z);
                }
                // Case 3: Uncle is black and z is left child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->left;
            if (y->color == RED)
            { // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                { // Case 2: Uncle is black and z is left child
                    z = z->parent;
                    rightRotate(tree, z);
                }
                // Case 3: Uncle is black and z is right child
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RBTree *tree, int data)
{
    Node *z = createNode(data, tree->NIL);
    Node *y = tree->NIL;
    Node *x = tree->root;

    while (x != tree->NIL)
    {
        y = x;
        if (z->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->NIL)
    {
        tree->root = z;
    }
    else if (z->data < y->data)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = tree->NIL;
    z->right = tree->NIL;
    z->color = RED;

    insertFixup(tree, z);
}

// Utility function to print the tree
void inorderPrint(Node *root, Node *NIL)
{
    if (root != NIL)
    {
        inorderPrint(root->left, NIL);
        printf("%d ", root->data);
        inorderPrint(root->right, NIL);
    }
}

int main()
{
    RBTree *tree = createTree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);

    printf("Inorder Traversal of Created Tree:\n");
    inorderPrint(tree->root, tree->NIL);
    printf("\n");

    return 0;
}
