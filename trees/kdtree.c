#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the number of dimensions (k)
#define K 2

// Structure to represent a k-d tree node
typedef struct KDNode
{
    int point[K];
    struct KDNode *left, *right;
} KDNode;

// Function to create a new k-d tree node
KDNode *newNode(int arr[])
{
    KDNode *temp = (KDNode *)malloc(sizeof(KDNode));
    for (int i = 0; i < K; i++)
    {
        temp->point[i] = arr[i];
    }
    temp->left = temp->right = NULL;
    return temp;
}

// Inserts a new node and returns the root of the modified tree
KDNode *insertRec(KDNode *root, int point[], unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
        return newNode(point);

    // Calculate current dimension (cd)
    unsigned cd = depth % K;

    // Compare the new point with the root on current dimension
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

// Function to insert a new point with given point[] in the k-d tree
KDNode *insert(KDNode *root, int point[])
{
    return insertRec(root, point, 0);
}

// A utility function to find minimum of three integers
int min(int x, int y, int z)
{
    return (x < y ? (x < z ? x : z) : (y < z ? y : z));
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
KDNode *findMinRec(KDNode *root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % K;

    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth + 1);
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode(root,
                   findMinRec(root->left, d, depth + 1),
                   findMinRec(root->right, d, depth + 1), d);
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
KDNode *findMin(KDNode *root, int d)
{
    return findMinRec(root, d, 0);
}

// Function to search a point in the k-d tree
bool searchRec(KDNode *root, int point[], unsigned depth)
{
    // Base cases
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    // Current dimension is calculated using current depth and total
    // dimensions (k)
    unsigned cd = depth % K;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

// A wrapper over searchRec()
bool search(KDNode *root, int point[])
{
    return searchRec(root, point, 0);
}

// Function to print points in the k-d tree
void printKDTree(KDNode *root)
{
    if (root != NULL)
    {
        printKDTree(root->left);
        printf("(%d, %d)\n", root->point[0], root->point[1]);
        printKDTree(root->right);
    }
}

// Utility function to compare two points
bool arePointsSame(int point1[], int point2[])
{
    for (int i = 0; i < K; ++i)
        if (point1[i] != point2[i])
            return false;
    return true;
}

int main()
{
    KDNode *root = NULL;
    int points[][K] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};

    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);

    // Print the k-d tree
    printf("K-d tree constructed:\n");
    printKDTree(root);

    // Search for points in the k-d tree
    int point1[] = {10, 19};
    (search(root, point1)) ? printf("Found\n") : printf("Not Found\n");

    int point2[] = {12, 19};
    (search(root, point2)) ? printf("Found\n") : printf("Not Found\n");

    return 0;
}
